#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int v;
    float peso;
    elemento* prox;
} elemento;

int main () {
    int blocks, paths;
    float folego;

    scanf("%i %i %f", &blocks, &paths, &folego);
    while (blocks != paths && paths != folego && folego != 0) {

        // Inicializei a lista
        elemento lista[blocks];
        for (int i = 0; i < blocks; i++) {
            lista[i].v = i;
            lista[i].peso = 0.0;
            lista[i].prox = NULL;
        }

        // Li todos os caminhos e preenchi a lista de adjacencia
        for (int i = 0; i < paths; i++) {
            int orig, dest;
            float peso;
            scanf("%i %i %f", &orig, &dest, &peso);
            elemento novo;
            novo.v = dest-1;
            novo.peso = peso;
            novo.prox = NULL;
            elemento target = lista[orig-1];
            while (target.prox != NULL) target = target.prox;
            target.prox = &novo;
        }

        

    }
}