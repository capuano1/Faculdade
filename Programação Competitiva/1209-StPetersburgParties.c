#include <stdio.h>
#include <string.h>

int cabeca[1005], dest[1000005], prox[1000005];
int grau[1005], saiu[1005], fila[1005];
int indice_aresta;

void add_aresta(int u, int v) {
    dest[indice_aresta] = v;
    prox[indice_aresta] = cabeca[u];
    cabeca[u] = indice_aresta++;
}

int main() {

    int n, m, k, u, v, i, inicio, fim, primeiro;

    while (scanf("%i %i %i", &n, &m, &k) != EOF) {
        
        memset(cabeca, -1, (n + 1) * sizeof(int));
        memset(grau, 0, (n + 1) * sizeof(int));
        memset(saiu, 0, (n + 1) * sizeof(int));
        indice_aresta = 0;

        for (i = 0; i < m; i++) {
            scanf("%i %i", &u, &v);
            add_aresta(u, v);
            add_aresta(v, u);
            grau[u]++;
            grau[v]++;
        }

        inicio = 0;
        fim = 0;
        for (i = 1; i <= n; i++) {
            if (grau[i] < k) {
                fila[fim++] = i;
                saiu[i] = 1;
            }
        }

        while (inicio < fim) {
            u = fila[inicio++];
            
            for (i = cabeca[u]; i != -1; i = prox[i]) {
                v = dest[i];
                
                if (!saiu[v]) {
                    grau[v]--;
                    if (grau[v] < k) {
                        saiu[v] = 1;
                        fila[fim++] = v;
                    }
                }
            }
        }

        primeiro = 1;
        for (i = 1; i <= n; i++) {
            if (!saiu[i]) {
                if (!primeiro) printf(" ");
                printf("%i", i);
                primeiro = 0;
            }
        }

        if (primeiro) {
            printf("0");
        }
        
        printf("\n");
    }

    return 0;
}