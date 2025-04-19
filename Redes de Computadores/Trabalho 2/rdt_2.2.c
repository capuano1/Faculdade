#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdint.h>
#include <fcntl.h>
#include <sys/time.h>

#include "rdt.h"

// Injetar erro de bit
int biterror_inject = FALSE;
// Sequências de envio e recebimento
hseq_t _snd_seqnum = 1;
hseq_t _rcv_seqnum = 1;
// Janelas de Transmissão
window_t send_window;
window_t recv_window;

#define TIMEOUT_INTERVAL 2

// Contagem do rtt como timeout
struct timeval send_time[WINDOW_SIZE];
struct timeval rtt;

// Inicializa as janelas
void initWindows() {
    send_window.base = 0;
    send_window.next_seqnum = 0;
    send_window.window_size = WINDOW_SIZE;
    memset(send_window.packets, 0, sizeof(send_window.packets));
    memset(send_window.ack_received, 0, sizeof(send_window.ack_received));
    memset(send_window.timers, 0, sizeof(send_window.timers));
    memset(send_window.in_use, 0, sizeof(send_window.in_use));
    recv_window.base = 0;
    recv_window.next_seqnum = 0;
    recv_window.window_size = WINDOW_SIZE;
    memset(recv_window.packets, 0, sizeof(recv_window.packets));
}

// Atualiza o RTT
void calculate_rtt(int seq_num) {
    struct timeval recv_time, diff;
    gettimeofday(&recv_time, NULL);
    timersub(&recv_time, &send_time[seq_num % WINDOW_SIZE], &diff);
    
    rtt = diff;
}

// Checksum
unsigned short checksum(unsigned short *buf, int nbytes) {
    register long sum = 0;

    // 2 bytes
    while (nbytes > 1) {
        sum += *(buf++);
        nbytes -= 2;
    }

    // Remanescente
    if (nbytes == 1) {
        sum += *(unsigned char *) buf;
    }

    // Carry-over
    while (sum >> 16) {
        sum = (sum & 0xffff) + (sum >> 16);
    }

    //printf("Somatório final: %ld\n", sum);
    return (unsigned short) ~sum;
}

// Verificar se está corrompido, usando o checksum
int iscorrupted(pkt *pr) {
    pkt pl = *pr;
    pl.h.csum = 0;
    unsigned short csuml;
    csuml = checksum((unsigned short *)&pl, pl.h.pkt_size);
    //printf("Checksum calculado: %u, Checksum esperado: %u\n", csuml, pr->h.csum);
    if (csuml != pr->h.csum) {
        return TRUE;
    }
    return FALSE;
}

// Criação de pacote
int make_pkt(pkt *p, htype_t type, hseq_t seqnum, void *msg, int msg_len) {
	if (msg_len > MAX_MSG_LEN) {
		printf("Tamanho da msg (%d) maior que limite: (%d).\n",
		msg_len, MAX_MSG_LEN);
		return ERROR;
	}
	p->h.pkt_size = sizeof(hdr);
	p->h.csum = 0;
	p->h.pkt_type = type;
	p->h.pkt_seq = seqnum;
	if (msg_len > 0) {
		p->h.pkt_size += msg_len;
		memset(p->msg, 0, MAX_MSG_LEN);
		memcpy(p->msg, msg, msg_len);
	}
	p->h.csum = checksum((unsigned short *)p, p->h.pkt_size);
	return SUCCESS;
}

// Verificar ACK
int has_ackseq(pkt *p, hseq_t seqnum) {
	if (p->h.pkt_type != PKT_ACK || p->h.pkt_seq != seqnum)
		return FALSE;
	return TRUE;
}

// Start timer do pacote
void start_timer(int seqnum) {
    clock_gettime(CLOCK_REALTIME, &send_window.timers[seqnum % send_window.window_size]);
}

// Checar tempo de envio e tempo de timeout
int is_timeout(int seqnum) {
    struct timespec now;
    clock_gettime(CLOCK_REALTIME, &now);

    struct timespec start = send_window.timers[seqnum % send_window.window_size];
    if (now.tv_sec - start.tv_sec > rtt.tv_sec) {
        return TRUE;
    }
    return FALSE;
}

// send()
int rdt_send(int sockfd, void *buf, int buf_len, struct sockaddr_in *dst) {
    pkt p, ack;
    struct sockaddr_in dst_ack;
    int ns, nr, addrlen;
    fd_set read_fds;
    struct timeval timeout;

    // Nao-bloqueante
    int flags = fcntl(sockfd, F_GETFL, 0);
    if (flags < 0) {
        perror("fcntl F_GETFL failed");
        close(sockfd);
        exit(EXIT_FAILURE);
    }
    flags = (flags | O_NONBLOCK);
    if (fcntl(sockfd, F_SETFL, flags) < 0) {
        perror("fcntl F_SETFL failed");
        close(sockfd);
        exit(EXIT_FAILURE);
    }

    while ((send_window.next_seqnum - send_window.base + WINDOW_SIZE) % WINDOW_SIZE >= WINDOW_SIZE) {
        timeout = rtt;  // Timeout com rtt
        FD_ZERO(&read_fds);
        FD_SET(sockfd, &read_fds);
        int ret = select(sockfd + 1, &read_fds, NULL, NULL, &timeout);
        if (ret > 0 && FD_ISSET(sockfd, &read_fds)) {
            addrlen = sizeof(struct sockaddr_in);
            nr = recvfrom(sockfd, &ack, sizeof(ack), 0, (struct sockaddr *)&dst_ack, (socklen_t *)&addrlen);
            while (nr > 0) {
                if (nr > 0 && !iscorrupted(&ack) && has_ackseq(&ack, ack.h.pkt_seq)) {
                    printf("ACK recebido para o pacote %d\n", ack.h.pkt_seq);
                    send_window.ack_received[ack.h.pkt_seq % send_window.window_size] = TRUE;
                    send_window.in_use[ack.h.pkt_seq % send_window.window_size] = FALSE;
                    calculate_rtt(ack.h.pkt_seq);  // Calcule o RTT aqui
                    if (ack.h.pkt_seq == send_window.base) {
                        send_window.base = ((send_window.base + 1) % (2*WINDOW_SIZE));
                        while (send_window.in_use[send_window.base % send_window.window_size]) {
                            printf("Base da janela avançada para %d\n", ((send_window.base + 1) % (2*WINDOW_SIZE))); // AQUI
                            send_window.base = ((send_window.base + 1) % (2*WINDOW_SIZE));
                        }
                    }
                } else {
                    //printf("Pacote ACK corrompido ou inválido\n");
                }
                nr = recvfrom(sockfd, &ack, sizeof(ack), 0, (struct sockaddr *)&dst_ack, (socklen_t *)&addrlen);
            }
        }
    }

    // Verifica se o espaço na janela está disponível para adicionar um novo pacote
    if (send_window.in_use[send_window.next_seqnum % send_window.window_size]) {
        printf("Espaço na janela não disponível para o pacote %d, aguardando...\n", send_window.next_seqnum);
        return rdt_send(sockfd, buf, buf_len, dst);
    }

    // Cria o pacote
    if (make_pkt(&p, PKT_DATA, send_window.next_seqnum, buf, buf_len) < 0)
        return ERROR;

    // Armazena o pacote na janela de transmissão
    send_window.packets[send_window.next_seqnum % send_window.window_size] = p;
    send_window.ack_received[send_window.next_seqnum % send_window.window_size] = FALSE;
    send_window.in_use[send_window.next_seqnum % send_window.window_size] = TRUE;
    gettimeofday(&send_time[send_window.next_seqnum % WINDOW_SIZE], NULL); //tempo de envio
    start_timer(send_window.next_seqnum);
    send_window.next_seqnum = (send_window.next_seqnum + 1) % (2 * WINDOW_SIZE);

    // send
    ns = sendto(sockfd, &p, p.h.pkt_size, 0, (struct sockaddr *)dst, sizeof(struct sockaddr_in));
    if (ns < 0) {
        perror("sendto(rdt_send) error:");
        return ERROR;
    }
    printf("Pacote %d enviado\n", p.h.pkt_seq);

    // ACKs e retransmissao
    while ((send_window.base - send_window.next_seqnum + WINDOW_SIZE) % WINDOW_SIZE != 0) {
        timeout = rtt;  // Use o RTT calculado como timeout
        FD_ZERO(&read_fds);
        FD_SET(sockfd, &read_fds);
        int ret = select(sockfd + 1, &read_fds, NULL, NULL, &timeout);

        if (ret == 0) {
            // Timeout, retransmite os pacotes não reconhecidos e dobra a duração do temporizador
            rtt.tv_sec *= 2;
            rtt.tv_usec *= 2;
            for (int i = send_window.base; (i % WINDOW_SIZE) != (send_window.next_seqnum % WINDOW_SIZE); i = (i + 1) % WINDOW_SIZE) {
                if (!send_window.ack_received[i % send_window.window_size] && is_timeout(i)) {
                    printf("Timeout: retransmitindo pacote %d...\n", i);
                    p = send_window.packets[i % send_window.window_size];
                    ns = sendto(sockfd, &p, p.h.pkt_size, 0, (struct sockaddr *)dst, sizeof(struct sockaddr_in));
                    if (ns < 0) {
                        perror("sendto(rdt_send) error:");
                        return ERROR;
                    }
                    start_timer(i);  // Reinicia o temporizador
                }
            }
        } else if (ret < 0) {
            perror("select() error");
            return ERROR;
        } else if (FD_ISSET(sockfd, &read_fds)) {
            addrlen = sizeof(struct sockaddr_in);
            nr = recvfrom(sockfd, &ack, sizeof(ack), 0, (struct sockaddr *)&dst_ack, (socklen_t *)&addrlen);
            while (nr > 0) {
                if (nr > 0 && !iscorrupted(&ack) && has_ackseq(&ack, ack.h.pkt_seq)) {
                    printf("ACK recebido para o pacote %d\n", ack.h.pkt_seq);
                    send_window.ack_received[ack.h.pkt_seq % send_window.window_size] = TRUE;
                    send_window.in_use[ack.h.pkt_seq % send_window.window_size] = FALSE;  // Libera o espaço
                    calculate_rtt(ack.h.pkt_seq);  // Calcule o RTT aqui
                    if (ack.h.pkt_seq == send_window.base) {
                        send_window.base = ((send_window.base + 1) % (2*WINDOW_SIZE));
                        while (send_window.in_use[send_window.base % send_window.window_size]) {
                            printf("Base da janela avançada para %d\n", ((send_window.base + 1) % (2*WINDOW_SIZE))); // AQUI
                            send_window.base = ((send_window.base + 1) % (2*WINDOW_SIZE));
                        }
                    }
                } else {
                    //printf("Pacote ACK corrompido ou inválido\n");
                }
                nr = recvfrom(sockfd, &ack, sizeof(ack), 0, (struct sockaddr *)&dst_ack, (socklen_t *)&addrlen);
            }
        }
    }

    return buf_len;
}

// Verifica se eh o pacote que queremos
int has_dataseqnum(pkt *p, hseq_t seqnum) {
	if (p->h.pkt_seq != seqnum || p->h.pkt_type != PKT_DATA)
		return FALSE;
	return TRUE;
}

// recv()
int rdt_recv(int sockfd, void *buf, int buf_len, struct sockaddr_in *src) {
    pkt p, ack;
    int nr, ns;
    int addrlen;
    fd_set read_fds;
    struct timeval timeout;

    memset(&p, 0, sizeof(hdr));

    if (make_pkt(&ack, PKT_ACK, recv_window.base - 1, NULL, 0) < 0)
        return ERROR;

rerecv:
    timeout.tv_sec = 10;  // Temporizador do recv grande para dar tempo de escrever o comando de send no outro terminal
    timeout.tv_usec = 0;

    FD_ZERO(&read_fds);
    FD_SET(sockfd, &read_fds);

    int ret = select(sockfd + 1, &read_fds, NULL, NULL, &timeout);
    if (ret == 0) {
        printf("Nenhum pacote recebido no tempo limite\n");
        return 0;  // Retorna 0 para indicar que nenhum dado foi recebido, mas sem erro
    } else if (ret < 0) {
        perror("select() error");
        return ERROR;
    }

    addrlen = sizeof(struct sockaddr_in);
    nr = recvfrom(sockfd, &p, sizeof(pkt), 0, (struct sockaddr *)src, (socklen_t *)&addrlen);
    if (nr < 0) {
        perror("recvfrom() error");
        return ERROR;
    }

    printf("Pacote %d recebido\n", p.h.pkt_seq);

    if (!iscorrupted(&p)) {
        int seq_index = p.h.pkt_seq % recv_window.window_size;

        if (has_dataseqnum(&p, recv_window.base)) {
            // Pacote esperado
            memcpy(buf, p.msg, p.h.pkt_size - sizeof(hdr));
            recv_window.base = ((recv_window.base + 1) % (2*WINDOW_SIZE));
        } else if (p.h.pkt_seq < recv_window.base + recv_window.window_size && p.h.pkt_seq >= recv_window.base) {
            // Pacote fora de ordem
            recv_window.packets[seq_index] = p;
        }

        // Enviar ACK
        if (make_pkt(&ack, PKT_ACK, p.h.pkt_seq, NULL, 0) < 0)
            return ERROR;

        ns = sendto(sockfd, &ack, ack.h.pkt_size, 0, (struct sockaddr *)src, (socklen_t)sizeof(struct sockaddr_in));
        if (ns < 0) {
            perror("ACK sendto(rdt_recv) error");
            return ERROR;
        }

        // Entrega pacote na ordem correta
        // Alterar pois servidor agora recebe o tamanho da mensagem e acessa direto o buffer
        // Janela de transmissao dinamica precisa mudar
        while (recv_window.base != recv_window.next_seqnum) {
            int seq_index = recv_window.base % recv_window.window_size;
            if (recv_window.packets[seq_index].h.pkt_seq == recv_window.base) {
                int msg_size = recv_window.packets[seq_index].h.pkt_size - sizeof(hdr);
                if (msg_size > buf_len) {
                    printf("Tamanho insuficiente: (%d) buffer para (%d).\n", buf_len, msg_size);
                    return ERROR;
                }
                memcpy(buf, recv_window.packets[seq_index].msg, msg_size);
                recv_window.base = ((recv_window.base + 1) % (2*WINDOW_SIZE));
            } else {
                break;
            }
        }
    } else {
        // Enviar último ACK se o pacote recebido estiver corrompido
        if (make_pkt(&ack, PKT_ACK, recv_window.base - 1, NULL, 0) < 0)
            return ERROR;
        ns = sendto(sockfd, &ack, ack.h.pkt_size, 0, (struct sockaddr *)src, (socklen_t)sizeof(struct sockaddr_in));
        if (ns < 0) {
            perror("ACK sendto(rdt_recv) error");
            return ERROR;
        }
    }

    return p.h.pkt_size - sizeof(hdr);
}

