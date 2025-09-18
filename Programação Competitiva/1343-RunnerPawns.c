#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_FILA 10000

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

