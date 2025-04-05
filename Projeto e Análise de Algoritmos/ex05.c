#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main (int argc, char** argv) {
    int numJogadores;
    scanf("%i", &numJogadores);
    numJogadores++;
    int escolhas[numJogadores];
    escolhas[0] = 0;
    int j;
    for (int i = 1; i < numJogadores; i++){
        scanf(" %i", &j);
        scanf(" %i", &escolhas[j]);
    }
    int grupo[numJogadores];
    int maiorGrupo[numJogadores];
    int tamanho = 0;
    int maior = 0;
    int i = 1;
    int ini = 1;
    while (ini < numJogadores) {
        memset(grupo, 0, sizeof(grupo));
        while (escolhas[ini] == 0) ini++;
        grupo[0] = ini;
        grupo[1] = escolhas[ini];
        i = escolhas[ini];
        escolhas[ini] = 0;
        tamanho = 2;
        int j = 2;
        while (escolhas[i] != 0) {
            grupo[j] = escolhas[i];
            i = grupo[j]; j++; tamanho++;
        }
        int aux = 0;
        while (grupo[aux] != i) aux++; tamanho--;
        if (tamanho <= 1) continue;
        if (tamanho > maior) {
            memset(maiorGrupo, 0, sizeof(grupo));
            for (int z = 0; aux < j; aux++, z++) {
                maiorGrupo[z] = grupo[aux];
            }
        }
    }
    for (int z = 0; z < maior; z++) printf("%i ", maiorGrupo[z]);
}