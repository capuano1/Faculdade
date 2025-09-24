#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int tempo;
    int pontos;
} Atracao;

int main () {
    int nRides, time, inst = 1;;

    scanf("%i %i", &nRides, &time);

    while (nRides && time) {
        Atracao opcoes[nRides];
        int *dynamic = calloc(time + 1, sizeof(int));

        for (int i = 0; i < nRides; i++) {
            scanf("%i %i", &opcoes[i].tempo, &opcoes[i].pontos);
        }

        for (int i = 0; i < nRides; i++) {
            // Se j fosse 0, no próximo if teríamos acesso à um índice negativo do array
            for (int j = opcoes[i].tempo; j < time + 1; j++) {
                // Se a pontuacao atual for menor do que ela seria se tivesse passado pela
                // atração i, isto é, gasto o tempo nela e ganhado os pontos
                if (dynamic[j] < dynamic[j - opcoes[i].tempo] + opcoes[i].pontos) {
                    dynamic[j] = dynamic[j - opcoes[i].tempo] + opcoes[i].pontos;
                }
            }
        }

        printf("Instancia %i\n", inst);
        printf("%i\n", dynamic[time]);
        printf("\n");

        free(dynamic);

        scanf("%i %i", &nRides, &time);

        inst++;

    }

    return 0;

}