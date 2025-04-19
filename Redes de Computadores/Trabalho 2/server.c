#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/time.h>
#include "rdt.h"

#define PORT 8080
#define BUFFER_SIZE 1024

// Recebe o arquivo e salva
void save_file(int sockfd, struct sockaddr_in *client_addr) {
    FILE *file = fopen("arquivo_recebido", "wb");
    if (file == NULL) {
        perror("Erro ao abrir o arquivo para escrita");
        return;
    }

    char buffer[BUFFER_SIZE];
    int bytes_received;

    while (1) {
        bytes_received = rdt_recv(sockfd, buffer, BUFFER_SIZE, client_addr);
        if (bytes_received < 0) {
            perror("RDT Falhou (recv)");
            fclose(file);
            return;
        }

        // Verifica se é o fim do arquivo
        if (strncmp(buffer, "EOF", 3) == 0) {
            break;
        }

        if (bytes_received > 0) {
            fwrite(buffer, 1, bytes_received, file);
        }
    }

    fclose(file);
    printf("Arquivo salvo com sucesso: arquivo_recebido\n");
}


int main() {
    int sockfd;
    struct sockaddr_in server_addr, client_addr;
    socklen_t addr_len = sizeof(client_addr);

    // Criar socket
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        perror("Socket Failure");
        exit(EXIT_FAILURE);
    }

    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);

    // Vincular socket
    if (bind(sockfd, (const struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("Bind Failure");
        exit(EXIT_FAILURE);
    }

    printf("Servidor iniciado na porta %d...\n", PORT);

    // Inicializa a janela
    initWindows();

    // Receber e salvar o arquivo
    save_file(sockfd, &client_addr);

    close(sockfd);
    return 0;
}
