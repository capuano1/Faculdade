#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main (int argc, char** argv) {
    int numJogadores;
    scanf("%i", &numJogadores);

    int* escolhas = (int*)calloc(numJogadores + 1, sizeof(int));
    int j;
    for (int i = 1; i <= numJogadores; i++) {
        scanf("%i", &j);
        if (j >= 1 && j <= numJogadores) {
            scanf("%i", &escolhas[j]);
        }
    }

    int* grupo = (int*)calloc(numJogadores + 1, sizeof(int));
    int* maiorGrupo = (int*)calloc(numJogadores + 1, sizeof(int));
    int tamanho = 0;
    int maior = 0;
    int i = 1;
    int ini = 1;

    while (ini <= numJogadores) {
        while (ini <= numJogadores && escolhas[ini] == 0) ini++;
        if (ini > numJogadores) break;

        int indiceGrupo = 0;
        grupo[indiceGrupo++] = ini;
        int prox = escolhas[ini];
        escolhas[ini] = 0;
        tamanho = 1;

        while (prox != 0) {
            grupo[indiceGrupo++] = prox;
            int temp = prox;
            prox = escolhas[prox];
            escolhas[temp] = 0;
            tamanho++;
        }

        int aux = 0;
        while (aux < indiceGrupo && grupo[aux] != grupo[indiceGrupo - 1]) aux++;
        tamanho -= aux;

        if (tamanho > maior) {
            maior = tamanho;
            memcpy(maiorGrupo, &grupo[aux], tamanho * sizeof(int));
        }
    }

    for (int z = 0; z < maior-1; z++) {
        printf("%i ", maiorGrupo[z]);
    }

    free(escolhas);
    free(grupo);
    free(maiorGrupo);

    return 0;
}
