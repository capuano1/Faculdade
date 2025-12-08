#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int origem, destino;
    int custo; 
} Ligacao;

int representante[200000];
int nivel[200000];

int fundir_conjuntos(int a, int b) {
    
    int raiz_a = a;
    int prox_no_a = a;
    
    while (raiz_a != representante[raiz_a]) {
        raiz_a = representante[raiz_a];
    }
    
    while (prox_no_a != raiz_a) {
        int temp = representante[prox_no_a];
        representante[prox_no_a] = raiz_a;
        prox_no_a = temp;
    }

    int raiz_b = b;
    int prox_no_b = b;
    
    while (raiz_b != representante[raiz_b]) {
        raiz_b = representante[raiz_b];
    }
    
    while (prox_no_b != raiz_b) {
        int temp = representante[prox_no_b];
        representante[prox_no_b] = raiz_b;
        prox_no_b = temp;
    } 
    
    if (raiz_a == raiz_b) {
        return 0;
    }
    
    if (nivel[raiz_a] < nivel[raiz_b]) {
        representante[raiz_a] = raiz_b;
    } else if (nivel[raiz_a] > nivel[raiz_b]) {
        representante[raiz_b] = raiz_a;
    } else {
        representante[raiz_b] = raiz_a;
        nivel[raiz_a]++;
    }
    
    return 1;
}

int ordenar_ligacoes(const void *ptr_a, const void *ptr_b) {
    Ligacao *lig_a = (Ligacao *)ptr_a;
    Ligacao *lig_b = (Ligacao *)ptr_b;
    
    if (lig_a->custo < lig_b->custo) return -1;
    if (lig_a->custo > lig_b->custo) return 1;
    return 0;
}

int main() {
    int vertices, num_ligacoes;
    
    while (scanf("%i %i", &vertices, &num_ligacoes) == 2 && (vertices != 0 || num_ligacoes != 0)) {
        
        Ligacao *todas_ligacoes = (Ligacao *)malloc(num_ligacoes * sizeof(Ligacao));
        int soma_total_custos = 0; 
        
        for (int i = 0; i < num_ligacoes; i++) {
            scanf("%i %i %i", &todas_ligacoes[i].origem, &todas_ligacoes[i].destino, &todas_ligacoes[i].custo);
            soma_total_custos += todas_ligacoes[i].custo;
        }
        
        qsort(todas_ligacoes, num_ligacoes, sizeof(Ligacao), ordenar_ligacoes);
        
        for (int i = 0; i < vertices; i++) {
            representante[i] = i;
            nivel[i] = 0; 
        }
        
        int custo_agm = 0;
        int ligacoes_na_agm = 0;
        
        for (int i = 0; i < num_ligacoes && ligacoes_na_agm < vertices - 1; i++) {
            if (fundir_conjuntos(todas_ligacoes[i].origem, todas_ligacoes[i].destino)) {
                custo_agm += todas_ligacoes[i].custo;
                ligacoes_na_agm++;
            }
        }
        
        int economia_maxima = soma_total_custos - custo_agm;
        printf("%i\n", economia_maxima);
        
        free(todas_ligacoes);
    }
    
    return 0;
}