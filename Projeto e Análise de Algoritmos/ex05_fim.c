#include <stdio.h>
#include <stdlib.h>

int comparar(const void *a, const void *b) {
    int valor1 = *(const int *)a;
    int valor2 = *(const int *)b;
    return valor1 - valor2;
}

int main() {
    int numeroDeJogadores;
    if (scanf("%d", &numeroDeJogadores) != 1) return 1;
    int *indicacoes = (int *) malloc((numeroDeJogadores + 1) * sizeof(int));
    int *grauEntrada = (int *) calloc(numeroDeJogadores + 1, sizeof(int));
    char *removidos = (char *) calloc(numeroDeJogadores + 1, sizeof(char));
    
    int x, y;
    for (int i = 0; i < numeroDeJogadores; i++) {
        scanf("%d %d", &x, &y);
        indicacoes[x] = y;
        grauEntrada[y]++;
    }
    
    int *fila = (int *) malloc((numeroDeJogadores + 1) * sizeof(int));
    int inicio = 0, fim = 0;
    
    for (int i = 1; i <= numeroDeJogadores; i++) {
        if (grauEntrada[i] == 0) {
            fila[fim++] = i;
        }
    }
    
    while (inicio < fim) {
        int jogador = fila[inicio++];
        removidos[jogador] = 1;
        int indicado = indicacoes[jogador];
        if (!removidos[indicado]) {
            grauEntrada[indicado]--;
            if (grauEntrada[indicado] == 0)
                fila[fim++] = indicado;
        }
    }
    
    int contagem = 0;
    for (int i = 1; i <= numeroDeJogadores; i++) {
        if (!removidos[i])
            contagem++;
    }
    
    int *resultado = (int *) malloc(contagem * sizeof(int));
    int indice = 0;
    for (int i = 1; i <= numeroDeJogadores; i++) {
        if (!removidos[i])
            resultado[indice++] = i;
    }
    
    qsort(resultado, contagem, sizeof(int), comparar);
    
    for (int i = 0; i < contagem; i++) {
        printf("%d ", resultado[i]);
    }
    printf("\n");
    
    free(indicacoes);
    free(grauEntrada);
    free(removidos);
    free(fila);
    free(resultado);
    
    return 0;
}
