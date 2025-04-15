#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include "rdt.h"

#define BUFFER_SIZE 1000
#define SEND_BUFFER_SIZE (BUFFER_SIZE * WINDOW_SIZE)

// Envio do arquivo em partes
void send_file(int sockfd, struct sockaddr_in *server_addr, const char *file_path) {
    FILE *file = fopen(file_path, "rb");
    if (file == NULL) {
        perror("Erro ao abrir o arquivo");
        exit(EXIT_FAILURE);
    }

    char buffer[BUFFER_SIZE];
    int bytes_read;

    while ((bytes_read = fread(buffer, 1, BUFFER_SIZE, file)) > 0) {
        if (rdt_send(sockfd, buffer, bytes_read, server_addr) < 0) {
            perror("rdt_send falhou");
            fclose(file);
            return;
        }
    }

    fclose(file);

    // Enviar uma mensagem indicando o fim do arquivo
    char end_of_file[] = "EOF";
    if (rdt_send(sockfd, end_of_file, strlen(end_of_file), server_addr) < 0) {
        perror("rdt_send falhou");
    }

    printf("Arquivo enviado com sucesso: %s\n", file_path);
}

int main(int argc, char *argv[]) {
    if (argc != 4) {
        fprintf(stderr, "Uso: %s <endereço_ip> <porta> <caminho_do_arquivo>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    int sockfd;
    struct sockaddr_in server_addr;

    // Criar Socket
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        perror("Socket Failure");
        exit(EXIT_FAILURE);
    }

    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(atoi(argv[2]));

    // Endereco IP
    if (inet_pton(AF_INET, argv[1], &server_addr.sin_addr) <= 0) {
        perror("Invalid or Unsupported Address");
        exit(EXIT_FAILURE);
    }

    printf("Conectado ao servidor %s:%s\n", argv[1], argv[2]);

    // Inicializa a janela de transmissão
    initWindows();

    // Enviar o arquivo
    send_file(sockfd, &server_addr, argv[3]);

    close(sockfd);
    return 0;
}
