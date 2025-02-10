#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdint.h>
#include <time.h>
#include <errno.h>

#include "rdt.h"

int biterror_inject = FALSE;
hseq_t _snd_seqnum = 1;
hseq_t _rcv_seqnum = 1;

unsigned short checksum(unsigned short *buf, int nbytes){
	register long sum;
	sum = 0;
	while (nbytes > 1) {
		sum += *(buf++);
		nbytes -= 2;
	}
	if (nbytes == 1)
		sum += *(unsigned short *) buf;
	while (sum >> 16)
		sum = (sum & 0xffff) + (sum >> 16);
	return (unsigned short) ~sum;
}

int iscorrupted(pkt *pr){
	pkt pl = *pr;
	pl.h.csum = 0;
	unsigned short csuml;
	csuml = checksum((void *)&pl, pl.h.pkt_size);
	if (csuml != pr->h.csum){
		return TRUE;
	}
	return FALSE;
}

int make_pkt(pkt *p, htype_t type, hseq_t seqnum, void *msg, int msg_len) {
	if (msg_len > MAX_MSG_LEN) {
		printf("make_pkt: tamanho da msg (%d) maior que limite (%d).\n",
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

int has_ackseq(pkt *p, hseq_t seqnum) {
	if (p->h.pkt_type != PKT_ACK || p->h.pkt_seq != seqnum)
		return FALSE;
	return TRUE;
}

struct timespec subtractTime(struct timespec tsa, struct timespec tsp) {
    struct timespec sampleRTT;
    sampleRTT.tv_sec = tsa.tv_sec - tsp.tv_sec;
    sampleRTT.tv_nsec = tsa.tv_nsec - tsp.tv_nsec;
    if (sampleRTT.tv_nsec < 0) {
        sampleRTT.tv_sec--;
        sampleRTT.tv_nsec += 1000000000;
    }
    return sampleRTT;
}

int rdt_send(int sockfd, void *buf, int buf_len, struct sockaddr_in *dst) {
    pkt p, ack;
    struct timeval timeout;
    struct timespec tsp, tsa, sampleRTT;
    struct sockaddr_in dst_ack;
    int ns, nr, addrlen;

    if (make_pkt(&p, PKT_DATA, _snd_seqnum, buf, buf_len) < 0)
        return ERROR;

    if (biterror_inject) {
        memset(p.msg, 0, MAX_MSG_LEN);
    }

resend:
	timeout.tv_sec = 5;
	timeout.tv_usec = 0;
    clock_gettime(CLOCK_REALTIME, &tsp);
    if (setsockopt(sockfd, SOL_SOCKET, SO_SNDTIMEO, &timeout, sizeof(timeout)) == -1) perror("Error setting timer");
    ns = sendto(sockfd, &p, p.h.pkt_size, 0,
                (struct sockaddr *)dst, sizeof(struct sockaddr_in));
    // if (errno == 11) nr = 0;  => 62 error EAGAIN EWOULDBLOCK => Timer Expired
    if (errno == 11) {
        perror("rdt_send: Timeout");
        goto resend;
    }
    if (ns < 0) {
        perror("rdt_send: sendto(PKT_DATA):");
        return ERROR;
    }
    addrlen = sizeof(struct sockaddr_in);
    if (setsockopt(sockfd, SOL_SOCKET, SO_RCVTIMEO, &timeout, sizeof(timeout)) == -1) perror("Error setting timer");
    // Bloqueante, mas precisa avisar o SO que existe um timeout => OK, setsockopt()
    nr = recvfrom(sockfd, &ack, sizeof(ack), 0, (struct sockaddr *)&dst_ack,
                  (socklen_t *)&addrlen);
    clock_gettime(CLOCK_REALTIME, &tsa);
    sampleRTT = subtractTime(tsa, tsp);
    if (errno == 11) {
        perror("rdt_send (recvfrom ACK): Timeout");
        goto resend;
    }
    // Problema: com o estouro do temporizador, nr fica negativo e entra nesse if
    if (nr < 0) {
        perror("rdt_send: recvfrom(PKT_ACK)");
        return ERROR;
    }

    if (iscorrupted(&ack) || !has_ackseq(&ack, _snd_seqnum)) {
        printf("rdt_send: iscorrupted || !has_ackseq\n");
        goto resend;
    }

    _snd_seqnum++;
    return buf_len;
}
int has_dataseqnum(pkt *p, hseq_t seqnum) {
	if (p->h.pkt_seq != seqnum || p->h.pkt_type != PKT_DATA)
		return FALSE;
	return TRUE;
}

int rdt_recv(int sockfd, void *buf, int buf_len, struct sockaddr_in *src) {
    pkt p, ack;
    int nr, ns;
    int addrlen;
    struct timeval timeout;
	

    memset(&p, 0, sizeof(hdr));

    if (make_pkt(&ack, PKT_ACK, _rcv_seqnum - 1, NULL, 0) < 0)
        return ERROR;

rerecv:
    timeout.tv_sec = 5;
	timeout.tv_usec = 0;
    if (setsockopt(sockfd, SOL_SOCKET, SO_RCVTIMEO, &timeout, sizeof(timeout)) == -1) perror("Error setting timer");
    addrlen = sizeof(struct sockaddr_in);
    nr = recvfrom(sockfd, &p, sizeof(pkt), 0, (struct sockaddr *)src,
                  (socklen_t *)&addrlen);
    
    if (errno == 11) {
        perror("rdt_recv: Timeout");
        goto rerecv;
    }
    
    if (nr < 0) {
        perror("recvfrom():");
        return ERROR;
    }

    if (iscorrupted(&p) || !has_dataseqnum(&p, _rcv_seqnum)) {
        printf("rdt_recv: iscorrupted || has_dataseqnum \n");
        // Enviar último ACK (_rcv_seqnum - 1)
        ns = sendto(sockfd, &ack, ack.h.pkt_size, 0,
                    (struct sockaddr *)src, (socklen_t)sizeof(struct sockaddr_in));
        if (ns < 0) {
            perror("rdt_rcv: sendto(PKT_ACK - 1)");
            return ERROR;
        }
        goto rerecv;
    }

    int msg_size = p.h.pkt_size - sizeof(hdr);
    if (msg_size > buf_len) {
        printf("rdt_rcv(): tamanho insuficiente de buffer (%d) para payload (%d).\n",
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
        perror("rdt_rcv: sendto(PKT_ACK)");
        return ERROR;
    }
    _rcv_seqnum++;
    return p.h.pkt_size - sizeof(hdr);
}
