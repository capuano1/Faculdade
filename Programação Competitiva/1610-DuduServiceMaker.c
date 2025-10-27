#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
0 = não visitado
1 = visitado anteriormente
2 = visitado nesta iteracao
*/

// Matriz de adjacencia: Memory Limit Exceeded

// Lista de adjacencia
typedef struct Noh {
    int vizinho;
    struct Noh *prox;
} Noh;

int buscaCiclo (Noh** adjList, int* estados, int n) {
    estados[n] = 2;
    
    Noh* atual = adjList[n];
    while (atual != NULL) {
        int i = atual->vizinho;
        if (estados[i] == 2) return 1;
        if (estados[i] == 0) {
            if (buscaCiclo(adjList, estados, i)) return 1;
        }
        atual = atual->prox;
    }
    estados[n] = 1;
    return 0;
}

int DFS (Noh** adjList, int docs) {
    int* estados = (int*) calloc(docs, sizeof(int));
    for (int i = 0; i < docs; i++) {
        if (estados[i] == 0) {
            if (buscaCiclo(adjList, estados, i)) {
                free(estados);
                return 1;
            }
        }
    }
    free(estados); 
    return 0;
}

int main () {
    int cases;

    if (scanf("%i", &cases) != 1) return 1;

    for (int i = 0; i < cases; i++) {
        int docs, depend;
        scanf("%i %i", &docs, &depend);

        Noh** adjList = (Noh**) calloc(docs, sizeof(Noh*));

        for (int j = 0; j < depend; j++) {
            int x, y;
            scanf("%i %i", &x, &y);
            
            Noh* newNoh = (Noh*) malloc(sizeof(Noh));
            newNoh->vizinho = y-1;
            
            newNoh->prox = adjList[x-1];
            adjList[x-1] = newNoh;
        }

        if (DFS(adjList, docs)) printf("SIM\n");
        else printf("NAO\n");

        for (int i = 0; i < docs; i++) {
            Noh *atual = adjList[i];
            Noh *prox;
            while (atual != NULL) {
                prox = atual->prox;
                free(atual);
                atual = prox;
            }
        }
        free(adjList);
    }
    return 0;
}