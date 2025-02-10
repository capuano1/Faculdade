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

        *send_buffer_len = 0; // Limpa o buffer de envio após o envio bem-sucedido
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
    init_send_window();

    while (1) {
        printf("Digite uma mensagem (ou 'sair' para encerrar): ");
        fgets(buffer, BUFFER_SIZE, stdin);
        buffer[strcspn(buffer, "\n")] = 0;

        if (strcmp(buffer, "sair") == 0) {
            break;
        }

        // Acumula mensagens no buffer de envio
        if (send_buffer_len + strlen(buffer) + 1 < SEND_BUFFER_SIZE) {
            memcpy(send_buffer + send_buffer_len, buffer, strlen(buffer));
            send_buffer_len += strlen(buffer);
            send_buffer[send_buffer_len++] = '\n'; // Adiciona nova linha como separador
        } else {
            // Envia o buffer acumulado se estiver cheio
            send_buffered_messages(sockfd, &server_addr, send_buffer, &send_buffer_len);
        }
    }

    // Envia o buffer acumulado restante
    send_buffered_messages(sockfd, &server_addr, send_buffer, &send_buffer_len);

    close(sockfd);
    return 0;
}
