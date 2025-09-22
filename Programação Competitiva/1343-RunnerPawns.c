#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_FILA 1000000

// Struct para representar os estados do jogo
typedef struct {
    int cavaloX, cavaloY;
    int peoes[8][2];
    // Booleano para peoes capturados
    int capturados[8];
    // Camada do BFS
    int rodada;
} Estado;

// Movimentos possíveis
int dx[8] = {-2, -2, -1, -1, 1, 1, 2, 2};
int dy[8] = {-1, 1, -2, 2, -2, 2, -1, 1};

int npeoes;
int peoesLidos[8][2];

void tradutor(int num, int *x, int *y) {
    num--;
    *x = num / 8;
    *y = num % 8;
}

// Booleano de verificação de estado de aceitação
int verificaSucesso(int capturados[]) {
    for (int i = 0; i < npeoes; i++) {
        if (!capturados[i]) return 0;
    }
    return 1;
}

// Verifica se o movimento foi válido
int posValida(int x, int y) {
    if (x >= 0 && x < 8 && y >= 0 && y < 8) return 1;
    return 0;
}

void novoEstado(Estado *novo, Estado *antigo) {
    novo->cavaloX = antigo->cavaloX;
    novo->cavaloY = antigo->cavaloY;
    novo->rodada = antigo->rodada;
    for (int i = 0; i < npeoes; i++) {
        novo->capturados[i] = antigo->capturados[i];
        novo->peoes[i][0] = antigo->peoes[i][0];
        novo->peoes[i][1] = antigo->peoes[i][1];
    }
}

int bfs (int cavaloX, int cavaloY) {
    Estado *fila = malloc(sizeof(Estado) * MAX_FILA);
    int frente = 0, tras = 0;

    Estado inicial;
    inicial.cavaloX = cavaloX; inicial.cavaloY = cavaloY; inicial.rodada = 0;
    for (int i = 0; i < npeoes; i++) {
        inicial.peoes[i][0] = peoesLidos[i][0];
        inicial.peoes[i][1] = peoesLidos[i][1];
        inicial.capturados[i] = 0;
    }

    if (tras >= MAX_FILA) {
        free(fila);
        return -1;
    }
    fila[tras] = inicial;
    tras++;

    while (frente < tras) {
        Estado atual = fila[frente];
        frente++;

        if (verificaSucesso(atual.capturados)) {
            free(fila);
            return atual.rodada;
        }

        for (int i = 0; i < 8; i++) {
            int nx = atual.cavaloX + dx[i];
            int ny = atual.cavaloY + dy[i];

            if (!posValida(nx, ny)) continue;

            Estado novo;
            novoEstado(&novo, &atual);
            novo.cavaloX = nx;
            novo.cavaloY = ny;

            int quebrou = 0;

            for (int j = 0; j < npeoes; j++) {
                // Se o peão não estiver capturado e for capturado no novo movimento do cavalo
                if (!novo.capturados[j] && novo.peoes[j][0] == nx && novo.peoes[j][1] == ny) {
                    novo.capturados[j] = 1;
                }
            }

            // Move os peões, mas só UMA VEZ para cada estado gerado pelo cavalo
            for (int j = 0; j < npeoes; j++) {
                if (!novo.capturados[j]) {
                    novo.peoes[j][0]++;
                    if (novo.peoes[j][0] >= 8) {
                        quebrou = 1;
                        break;
                    }
                    if (novo.peoes[j][0] == novo.cavaloX && novo.peoes[j][1] == novo.cavaloY) {
                        quebrou = 1;
                        break;
                    }
                }
            }
            if (quebrou) continue;

            // Incrementa a rodada após todos os movimentos serem completados
            novo.rodada++;

            if (tras >= MAX_FILA) {
                free(fila);
                return -1;
            }

            fila[tras] = novo;
            tras++;
        }
    }
    free(fila);
    return -1;
}

int main () {
    int cavalo, cavaloX, cavaloY;

    scanf("%i", &npeoes);

    while (npeoes != 0) {
        for (int i = 0; i < npeoes; i++) {
            int place;
            scanf("%i", &place);
            tradutor(place, &peoesLidos[i][0], &peoesLidos[i][1]);
        }

        scanf("%i", &cavalo);
        tradutor(cavalo, &cavaloX, &cavaloY);

        int resultado = bfs(cavaloX, cavaloY);
        if (resultado == -1) printf("impossible\n");
        else printf("%i\n", resultado);

        scanf("%i", &npeoes);
    }
    return 0;
}