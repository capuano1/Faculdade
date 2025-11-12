#include <stdio.h>
#include <stdlib.h>

#define LIMITE 100001 

// Fila
typedef struct {
    int numero;
    int passos;
} Estado;

int visitado[LIMITE];

int bfs(int N, int M) {
    if (N == M) return 0;
    for (int i = 0; i < LIMITE; i++) visitado[i] = 0;

    Estado* fila = (Estado*) malloc(LIMITE * sizeof(Estado));
    if (fila == NULL) return -1;

    int inicioFila = 0;
    int fimFila = 0;

    fila[fimFila].numero = N;
    fila[fimFila].passos = 0;
    fimFila++;
    
    visitado[N] = 1;

    while (inicioFila < fimFila) {
        Estado atual = fila[inicioFila];
        inicioFila++;

        int num_atual = atual.numero;
        int passos_atuais = atual.passos;

        if (num_atual == M) {
            free(fila);
            return passos_atuais;
        }

        int proximo_num;
        proximo_num = num_atual * 2;
        if (proximo_num < LIMITE && proximo_num >= 1 && visitado[proximo_num] == 0) {
            visitado[proximo_num] = 1;
            fila[fimFila].numero = proximo_num;
            fila[fimFila].passos = passos_atuais + 1;
            fimFila++;
        }
        
        proximo_num = num_atual * 3;
        if (proximo_num < LIMITE && proximo_num >= 1 && visitado[proximo_num] == 0) {
            visitado[proximo_num] = 1;
            fila[fimFila].numero = proximo_num;
            fila[fimFila].passos = passos_atuais + 1;
            fimFila++;
        }
        
        proximo_num = num_atual + 1;
        if (proximo_num < LIMITE && visitado[proximo_num] == 0) {
            visitado[proximo_num] = 1;
            fila[fimFila].numero = proximo_num;
            fila[fimFila].passos = passos_atuais + 1;
            fimFila++;
        }

        proximo_num = num_atual - 1;
        if (proximo_num >= 1 && proximo_num < LIMITE && visitado[proximo_num] == 0) {
            visitado[proximo_num] = 1;
            fila[fimFila].numero = proximo_num;
            fila[fimFila].passos = passos_atuais + 1;
            fimFila++;
        }

        if (num_atual % 2 == 0) {
            proximo_num = num_atual / 2;
            if (proximo_num >= 1 && proximo_num < LIMITE && visitado[proximo_num] == 0) {
                visitado[proximo_num] = 1;
                fila[fimFila].numero = proximo_num;
                fila[fimFila].passos = passos_atuais + 1;
                fimFila++;
            }
        }
        
        if (num_atual % 3 == 0) {
            proximo_num = num_atual / 3;
            if (proximo_num >= 1 && proximo_num < LIMITE && visitado[proximo_num] == 0) {
                visitado[proximo_num] = 1;
                fila[fimFila].numero = proximo_num;
                fila[fimFila].passos = passos_atuais + 1;
                fimFila++;
            }
        }
    }
    
    free(fila);
    return -1;
}

int main() {
    int N, M;
    while (scanf("%d %d", &N, &M) == 2) {
        int resultado = bfs(N, M);
        printf("%d\n", resultado);
    }

    return 0;
}