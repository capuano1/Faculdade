#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include "rdt.h"

#define BUFFER_SIZE 1024
#define SEND_BUFFER_SIZE (BUFFER_SIZE * WINDOW_SIZE)

void send_buffered_messages(int sockfd, struct sockaddr_in *server_addr, char *send_buffer, int *send_buffer_len) {
    if (*send_buffer_len > 0) {
        int retries = 0;
        int max_retries = 5;
        int timeout = 1000;

        while (retries < max_retries) {
            if (rdt_send(sockfd, send_buffer, *send_buffer_len, server_addr) < 0) {
                perror("rdt_send falhou");
                usleep(timeout * 1000);
                timeout *= 2;
                retries++;
            } else {
                break;
            }
        }

        if (retries == max_retries) {
            printf("Máximo de tentativas (%d) excedido\n", max_retries);
        }

        *send_buffer_len = 0; // Limpa o buffer de envio

		// Receber resposta do servidor
		char response[BUFFER_SIZE];
		struct sockaddr_in from_addr;
		socklen_t from_len = sizeof(from_addr);
		int recv_len = rdt_recv(sockfd, response, BUFFER_SIZE, &from_addr);
		if (recv_len < 0) {
			perror("RDT Falhou (recv)");
		}
		response[recv_len] = '\0';

		printf("Resposta do servidor: %s\n", response);

    }
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Uso: %s <endereço_ip> <porta>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    int sockfd;
    struct sockaddr_in server_addr;
    char buffer[BUFFER_SIZE];
    char send_buffer[SEND_BUFFER_SIZE];
    int send_buffer_len = 0;

    // Criar Socket
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        perror("Socket Failure");
        exit(EXIT_FAILURE);
    }

    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(atoi(argv[2]));
    
    if (inet_pton(AF_INET, argv[1], &server_addr.sin_addr) <= 0) {
        perror("Invalid or Unsupported Address");
        exit(EXIT_FAILURE);
    }

    printf("Conectado ao servidor %s:%s\n", argv[1], argv[2]);

    // Inicializa a janela de transmissão
    initWindows();
	int numMessages = 0;
    while (1) {
        printf("Digite uma mensagem (ou 'sair' para encerrar, 'send' para enviar o buffer): ");
        fgets(buffer, BUFFER_SIZE, stdin);
        buffer[strcspn(buffer, "\n")] = 0;

        if (strcmp(buffer, "sair") == 0) {
            break;
        }
		else if (strcmp(buffer, "send") == 0) {
            goto enviar;
        }

        // Acumula mensagens no buffer de envio
        if (send_buffer_len + strlen(buffer) + 1 < SEND_BUFFER_SIZE && numMessages < 4) {
            numMessages++;
			memcpy(send_buffer + send_buffer_len, buffer, strlen(buffer));
            send_buffer_len += strlen(buffer);
            send_buffer[send_buffer_len++] = '\n'; // Adiciona nova linha como separador
        } else {
			memcpy(send_buffer + send_buffer_len, buffer, strlen(buffer));
            send_buffer_len += strlen(buffer);
            send_buffer[send_buffer_len++] = '\n';
            // Envia o buffer acumulado se estiver cheio ou se tiverem 5 mensagens ou se o usuário quiser
			enviar:
			numMessages = 0;
            send_buffered_messages(sockfd, &server_addr, send_buffer, &send_buffer_len);
        }
    }

    close(sockfd);
    return 0;
}
