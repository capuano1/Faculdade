#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main (int argc, char** argv) {
    int numJogadores;
    scanf("%i", &numJogadores);

    int escolhas[numJogadores + 1];
    escolhas[0] = 0;
    
    int j;
    for (int i = 1; i <= numJogadores; i++) {
        scanf("%i", &j);
        if (j >= 1 && j <= numJogadores) {
            scanf("%i", &escolhas[j]);
        }
    }

    int grupo[numJogadores + 1];
    int maiorGrupo[numJogadores + 1];
    int tamanho = 0;
    int maior = 0;
    int i = 1;
    int ini = 1;

    while (ini <= numJogadores) {
        memset(grupo, 0, sizeof(grupo));
        while (ini <= numJogadores && escolhas[ini] == 0) ini++;
        if (ini > numJogadores) break;
        
        grupo[0] = ini;
        grupo[1] = escolhas[ini];
        i = escolhas[ini];
        escolhas[ini] = 0;
        tamanho = 2;

        int j = 2;
        while (i <= numJogadores && escolhas[i] != 0) {
            grupo[j] = escolhas[i];
            i = grupo[j];
            j++;
            tamanho++;
        }

        int aux = 0;
        while (grupo[aux] != i && aux < tamanho) aux++;
        tamanho = tamanho - aux;
        
        if (tamanho > maior) {
            maior = tamanho;
            memset(maiorGrupo, 0, sizeof(maiorGrupo));
            for (int z = 0; aux < j; aux++, z++) {
                maiorGrupo[z] = grupo[aux];
            }
        }
    }

    for (int z = 0; z < maior-1; z++) {
        printf("%i ", maiorGrupo[z]);
    }

    return 0;
}