#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int i;
} Coordenadas;

void pintar(int* matriz, int linhas, int colunas, int i, Coordenadas* fila) {
    int size = linhas * colunas;
    int inicioFila = 0;
    int fimFila = 0;
    
    fila[fimFila].i = i;
    fimFila++;

    matriz[i] = 1;

    while (inicioFila < fimFila) {
        Coordenadas atual = fila[inicioFila];
        inicioFila++;

        int x = atual.i;

        if (((x + 1) % colunas) != 0 && matriz[x + 1] == 0 && x + 1 < size) {
            fila[fimFila].i = x + 1;
            fimFila++;
            matriz[x + 1] = 1;
        }
        if (((x - 1) % colunas) != (colunas - 1) && matriz[x - 1] == 0 && x - 1 >= 0) {
            fila[fimFila].i = x - 1;
            fimFila++;
            matriz[x - 1] = 1;
        }
        if ((x + colunas) < size && matriz[x + colunas] == 0) {
            fila[fimFila].i = x + colunas;
            fimFila++;
            matriz[x + colunas] = 1;
        }
        if ((x - colunas) >= 0 && matriz[x - colunas] == 0) {
            fila[fimFila].i = x - colunas;
            fimFila++;
            matriz[x - colunas] = 1;
        }
    }
}

int main () {
    int linhas, colunas;
    scanf("%i %i", &linhas, &colunas);
    int* matriz;
    matriz = malloc(linhas * colunas * sizeof(int));
    Coordenadas* fila;
    fila = malloc(linhas * colunas * sizeof(Coordenadas));

    for (int i = 0; i < linhas * colunas; i++) {
        char lido;
        scanf(" %c", &lido);
        //printf("Lido: %c\n", lido);
        if (lido == '.') matriz[i] = 0;
        else matriz[i] = 1;
    }

    int contador = 0;
    for (int i = 0; i < linhas * colunas; i++) {
        if (matriz[i] == 0) {
            contador++;
            //printf("Chamei em %i e %i\n", i, j);
            pintar(matriz, linhas, colunas, i, fila);
        }
    }

    printf("%i\n", contador);
    free(matriz);
    free(fila);
    return 0;
}