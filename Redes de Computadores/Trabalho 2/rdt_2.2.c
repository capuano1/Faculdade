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

// Checksum
unsigned short checksum(unsigned short *buf, int nbytes) {
    register long sum = 0;
    //printf("Tamanho do buffer: %d\n", nbytes);

    // 2 bytes
    while (nbytes > 1) {
        sum += *(buf++);
        //printf("Somatório parcial: %ld\n", sum);
        nbytes -= 2;
    }

    // byte remanescente
    if (nbytes == 1) {
        sum += *(unsigned char *) buf;
        //printf("Somatório com byte extra: %ld\n", sum);
    }

    // carry-over
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

    // Cria Pacote
    if (make_pkt(&p, PKT_DATA, _snd_seqnum, buf, buf_len) < 0)
        return ERROR;
    // Zerar mensagem se tiver erro de bit
    if (biterror_inject) {
        memset(p.msg, 0, MAX_MSG_LEN);
    }

// Send Loop
resend:
    // Timeout
    timeout.tv_sec = 2;
    timeout.tv_usec = 0;

    // Configurar FDs e adicionar socket aos FDs
    FD_ZERO(&read_fds); FD_SET(sockfd, &read_fds);

    // Select -> timeout (setsockopt() não funciona de jeito nenhum)
    int ret = select(sockfd + 1, &read_fds, NULL, NULL, &timeout);

    // Send -> Envia pacote e relata erros caso não consiga
    ns = sendto(sockfd, &p, p.h.pkt_size, 0,
                (struct sockaddr *)dst, sizeof(struct sockaddr_in));
    if (ret == 0) {
        printf("Timeout: tentando retransmitir pacote...\n");
        goto resend;
    } else if (ret < 0) {
        perror("select() error");
        return ERROR;
    }
    if (ns < 0) {
        perror("sendto(rdt_send) error:");
        return ERROR;
    }

    // Recepção do ACK
    addrlen = sizeof(struct sockaddr_in);
    nr = recvfrom(sockfd, &ack, sizeof(ack), 0, (struct sockaddr *)&dst_ack,
                  (socklen_t *)&addrlen);
    if (nr < 0) {
        perror("ACK recvfrom(rdt_send) error");
        return ERROR;
    }

    // Verifica ACK
    if (iscorrupted(&ack) || !has_ackseq(&ack, _snd_seqnum)) {
        //printf("iscorrupted or !has_ackseq error\n");
        goto resend;
    }

    _snd_seqnum++;
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

    // Inicializar pacote vazio
    memset(&p, 0, sizeof(hdr));

    // Criar ACK
    if (make_pkt(&ack, PKT_ACK, _rcv_seqnum - 1, NULL, 0) < 0)
        return ERROR;

// recv loop
rerecv:
    // Timeout
    timeout.tv_sec = 5;
    timeout.tv_usec = 0;

    // Configura FDs e adiciona socket aos FDs
    FD_ZERO(&read_fds); FD_SET(sockfd, &read_fds);

    // select() -> Timeout (ao invés de setsockopt, que não estava funcionando)
    int ret = select(sockfd + 1, &read_fds, NULL, NULL, &timeout);
    if (ret == 0) {
        printf("Nenhum pacote recebido\n");
        return ERROR;
    } else if (ret < 0) {
        // Erro no select()
        perror("select() error");
        return ERROR;
    }

    // Recebe pacote
    addrlen = sizeof(struct sockaddr_in);
    nr = recvfrom(sockfd, &p, sizeof(pkt), 0, (struct sockaddr *)src,
                  (socklen_t *)&addrlen);
    if (nr < 0) {
        perror("recvfrom() error");
        return ERROR;
    }

    // Verifica se pacote está corrompido ou número de sequência não corresponde
    if (iscorrupted(&p) || !has_dataseqnum(&p, _rcv_seqnum)) {
        //printf("rdt_recv: iscorrupted || has_dataseqnum \n");
        ns = sendto(sockfd, &ack, ack.h.pkt_size, 0,
                    (struct sockaddr *)src, (socklen_t)sizeof(struct sockaddr_in));
        if (ns < 0) {
            perror("sendto(rdt_recv) error");
            return ERROR;
        }
        goto rerecv;
    }

    // Processa mensagem recebida
    int msg_size = p.h.pkt_size - sizeof(hdr);
    if (msg_size > buf_len) {
        printf("Insuficient size: (%d) buffer for (%d).\n",
               buf_len, msg_size);
        return ERROR;
    }
    memcpy(buf, p.msg, msg_size);

    // Enviar ACK
    if (make_pkt(&ack, PKT_ACK, p.h.pkt_seq, NULL, 0) < 0)
        return ERROR;

    ns = sendto(sockfd, &ack, ack.h.pkt_size, 0,
                (struct sockaddr *)src, (socklen_t)sizeof(struct sockaddr_in));
    if (ns < 0) {
        perror("ACK sendto(rdt_recv) error");
        return ERROR;
    }
    _rcv_seqnum++;
    return p.h.pkt_size - sizeof(hdr);
}
