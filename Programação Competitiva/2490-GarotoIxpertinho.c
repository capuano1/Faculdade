#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef struct elemento_struct {
    int v;
    double peso;
    struct elemento_struct* prox;
} elemento;

elemento* criar_elemento(int dest, double peso) {
    elemento* novo = (elemento*)malloc(sizeof(elemento));
    novo->v = dest;
    novo->peso = peso;
    novo->prox = NULL;
    return novo;
}

int arvminima (elemento lista[], int blocks, double folego) {
    int visitados[blocks];
    double custo_min[blocks]; 
    int total_visitados = 0;
    double total_peso = 0.0;
    int perdas_folego = 0;

    for(int i = 0; i < blocks; i++) {
        visitados[i] = 0;
        custo_min[i] = 999999999;
    }

    custo_min[0] = 0.0;
    
    while (total_visitados < blocks) {
        double min_custo = 999999999;
        int u = -1;
        
        for (int i = 0; i < blocks; i++) {
            if (visitados[i] == 0 && custo_min[i] < min_custo) {
                min_custo = custo_min[i];
                u = i;
            }
        }
        if (u == -1) {
            break; 
        }

        visitados[u] = 1;
        total_visitados++;
        
        if (min_custo > folego) {
            total_peso += min_custo + 2.0;
            perdas_folego++;
        } else {
            total_peso += min_custo;
        }
        
        elemento* aresta = lista[u].prox;

        while (aresta != NULL) {
            int v = aresta->v;
            double peso = aresta->peso;
            
            if (visitados[v] == 0 && peso < custo_min[v]) {
                custo_min[v] = peso;
            }
            aresta = aresta->prox;
        }
    }

    // Para corrigir o erro do 336.48 e 336.47
    total_peso = floor(total_peso * 100.0) / 100.0;
    printf("%.2f %d\n", total_peso, perdas_folego);
    return 1;
}

int main () {
    int blocks, paths;
    double folego;

    while (scanf("%i %i %lf", &blocks, &paths, &folego) && (blocks != 0 || paths != 0 || folego != 0)) {

        // Inicializei a lista (lista de adjacencia)
        elemento lista[blocks];
        for (int i = 0; i < blocks; i++) {
            lista[i].v = i;
            lista[i].peso = 0.0;
            lista[i].prox = NULL;
        }

        // Li todos os caminhos e preenchi a lista de adjacencia
        for (int i = 0; i < paths; i++) {
            int orig, dest;
            double peso;
            
            scanf("%i %i %lf", &orig, &dest, &peso);
            
            elemento* novo_orig = criar_elemento(dest - 1, peso);
            elemento* current_orig = &lista[orig - 1];
            while (current_orig->prox != NULL) {
                current_orig = current_orig->prox;
            }
            current_orig->prox = novo_orig;
            
            elemento* novo_dest = criar_elemento(orig - 1, peso);
            elemento* current_dest = &lista[dest - 1];

            while (current_dest->prox != NULL) {
                current_dest = current_dest->prox;
            }
            current_dest->prox = novo_dest;
        }

        arvminima(lista, blocks, folego);

        for (int i = 0; i < blocks; i++) {
            elemento* current = lista[i].prox;
            elemento* next;
            while (current != NULL) {
                next = current->prox;
                free(current);
                current = next;
            }
        }
    }
    return 0;
}