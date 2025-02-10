#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include "rdt.h"

#define BUFFER_SIZE 1024

int main(int argc, char *argv[]) {
    // Código padrão Linux mostrando como usar o comando
	if (argc != 3) {
        fprintf(stderr, "Uso: %s <endereço_ip> <porta>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

	// Socket, endereço do servidor e buffer
    int sockfd;
    struct sockaddr_in server_addr;
    char buffer[BUFFER_SIZE];

	// Criar Socket UDP (SOCK_DGRAM)
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        perror("Socket Failure");
        exit(EXIT_FAILURE);
    }

	// Definindo servidor para o formato correto
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(atoi(argv[2]));
    
	// Converte endereçp IP fornecido em endereço válido
    if (inet_pton(AF_INET, argv[1], &server_addr.sin_addr) <= 0) {
        perror("Invalid or Unsupported Address");
        exit(EXIT_FAILURE);
    }

    printf("Conectado ao servidor %s:%s\n", argv[1], argv[2]);

	// Main Loop
    while (1) {
		// Menu
		printf("Digite uma mensagem (ou 'sair' para encerrar): ");
		fgets(buffer, BUFFER_SIZE, stdin);
		buffer[strcspn(buffer, "\n")] = 0;

		if (strcmp(buffer, "sair") == 0) {
			break;
		}

		// Tentativas, Máximo e Timeout (multiplicado por 1000 novamente depois, por estar em usegundos)
		int retries = 0;
		int max_retries = 5;
		int timeout = 1000;

		// Tenta enviar a mensagem
		while (retries < max_retries) {
			if (rdt_send(sockfd, buffer, strlen(buffer), &server_addr) < 0) {
				perror("rdt_send falhou");
				usleep(timeout * 1000);
				timeout *= 2;
				retries++;
			} else {
				break;
			}
		}

		// Erro
		if (retries == max_retries) {
			printf("Máximo de tentativas (%d) excedido\n", max_retries);
			continue;
		}

		// Receber resposta do servidor
		char response[BUFFER_SIZE];
		struct sockaddr_in from_addr;
		socklen_t from_len = sizeof(from_addr);
		int recv_len = rdt_recv(sockfd, response, BUFFER_SIZE, &from_addr);
		if (recv_len < 0) {
			perror("RDT Falhou (recv)");
			continue;
		}
		response[recv_len] = '\0';

		printf("Resposta do servidor: %s\n", response);
	}
	// close do file descriptor do socket
    close(sockfd);
    return 0;
}
