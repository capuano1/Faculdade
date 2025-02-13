#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdint.h>

#include "rdt.h"

// Injetar erro de bit
int biterror_inject = FALSE;
// Sequências de envio e recebimento
hseq_t _snd_seqnum = 1;
hseq_t _rcv_seqnum = 1;
// Janelas de Transmissão
window_t send_window;
window_t recv_window;

void initWindows() {
    send_window.base = 0;
    send_window.next_seqnum = 0;
    send_window.window_size = WINDOW_SIZE;
    memset(send_window.packets, 0, sizeof(send_window.packets));
    recv_window.base = 0;
    recv_window.next_seqnum = 0;
    recv_window.window_size = WINDOW_SIZE;
    memset(recv_window.packets, 0, sizeof(recv_window.packets));
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

// send()
int rdt_send(int sockfd, void *buf, int buf_len, struct sockaddr_in *dst) {
    pkt p, ack;
    struct sockaddr_in dst_ack;
    int ns, nr, addrlen;
    fd_set read_fds;
    struct timeval timeout;

    if ((send_window.next_seqnum - send_window.base) < send_window.window_size) {
        // Cria o pacote de dados
        if (make_pkt(&p, PKT_DATA, send_window.next_seqnum, buf, buf_len) < 0)
            return ERROR;

        // Armazena o pacote na janela de transmissão
        send_window.packets[send_window.next_seqnum % send_window.window_size] = p;
        send_window.next_seqnum++;

        // Envia o pacote de dados
        ns = sendto(sockfd, &p, p.h.pkt_size, 0, (struct sockaddr *)dst, sizeof(struct sockaddr_in));
        if (ns < 0) {
            perror("sendto(rdt_send) error:");
            return ERROR;
        }
    }
    int retry = 0;
    // Aguarda pelo ACK
    while (send_window.base < send_window.next_seqnum && retry != 6) {
        timeout.tv_sec = 2;
        timeout.tv_usec = 0;
        FD_ZERO(&read_fds);
        FD_SET(sockfd, &read_fds);
        int ret = select(sockfd + 1, &read_fds, NULL, NULL, &timeout);

        // Em inglês pois eu tenho consumido tanto conteúdo em inglês, além de dar aula do idioma, que estou começando a falar igual ao Supla
        // Do tell me se você ler isso, papito
        // Se eu já reenviei a mensagem 5 vezes e não recebi um ACK, provavelmente o destinatário recebeu a mensagem, mas o ACK se perdeu
        if (retry == 5) {
            printf("Did not receive ACK after 5 retries. Server probably got the message, but might have lost packets\n");
            retry++;
            break;
        }
        else if (ret == 0 && retry < 5) {
            retry++;
            // Timeout, retransmite os pacotes na janela
            printf("Timeout: retransmitindo pacotes...\n");
            for (int i = send_window.base; i < send_window.next_seqnum; i++) {
                p = send_window.packets[i % send_window.window_size];
                ns = sendto(sockfd, &p, p.h.pkt_size, 0, (struct sockaddr *)dst, sizeof(struct sockaddr_in));
                if (ns < 0) {
                    perror("sendto(rdt_send) error:");
                    return ERROR;
                }
            }
        } else if (ret < 0) {
            perror("select() error");
            return ERROR;
        } else if (FD_ISSET(sockfd, &read_fds)) {
            addrlen = sizeof(struct sockaddr_in);
            nr = recvfrom(sockfd, &ack, sizeof(ack), 0, (struct sockaddr *)&dst_ack, (socklen_t *)&addrlen);
            if (nr < 0) {
                perror("ACK recvfrom(rdt_send) error");
                return ERROR;
            }

            if (!iscorrupted(&ack) && has_ackseq(&ack, send_window.base)) {
                send_window.base++;
            }
        }
    }

    return buf_len;
}

// Verifica número de sequência
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
    timeout.tv_sec = 5;
    timeout.tv_usec = 0;

    FD_ZERO(&read_fds);
    FD_SET(sockfd, &read_fds);

    int ret = select(sockfd + 1, &read_fds, NULL, NULL, &timeout);
    if (ret == 0) {
        printf("Nenhum pacote recebido\n");
        return ERROR;
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

    if (!iscorrupted(&p)) {
        int seq_index = p.h.pkt_seq % recv_window.window_size;

        if (has_dataseqnum(&p, recv_window.base)) {
            // Pacote esperado
            memcpy(buf, p.msg, p.h.pkt_size - sizeof(hdr));
            recv_window.base++;
        } else if (p.h.pkt_seq < recv_window.base + recv_window.window_size && p.h.pkt_seq >= recv_window.base) {
            // Pacote dentro da janela, mas fora de ordem
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

        // Entregar pacotes em ordem
        while (recv_window.base < recv_window.next_seqnum) {
            seq_index = recv_window.base % recv_window.window_size;
            if (recv_window.packets[seq_index].h.pkt_seq == recv_window.base) {
                int msg_size = recv_window.packets[seq_index].h.pkt_size - sizeof(hdr);
                if (msg_size > buf_len) {
                    printf("Insuficient size: (%d) buffer for (%d).\n", buf_len, msg_size);
                    return ERROR;
                }
                memcpy(buf, recv_window.packets[seq_index].msg, msg_size);
                recv_window.base++;
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
