#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <omp.h>

#define N 1000  // Tamanho da grade
#define T 1000 // Número de iterações
#define D 0.1  // Coeficiente de difusão
#define DELTA_T 0.01
#define DELTA_X 1.0
int t = 1;

void diff_eq(double** C, double** C_new) {
    for (int t = 0; t < T; t++) {
        #pragma omp parallel for collapse(2) num_threads(t)
        for (int i = 1; i < N - 1; i++) {
            for (int j = 1; j < N - 1; j++) {
                C_new[i][j] = C[i][j] + D * DELTA_T * (
                    (C[i+1][j] + C[i-1][j] + C[i][j+1] + C[i][j-1] - 4 * C[i][j]) / (DELTA_X * DELTA_X)
                );
            }
        }
        double difmedio = 0.;
        #pragma omp parallel for collapse(2) reduction(+:difmedio) num_threads(t)
        for (int i = 1; i < N - 1; i++) {
            for (int j = 1; j < N - 1; j++) {
                difmedio += fabs(C_new[i][j] - C[i][j]);
                C[i][j] = C_new[i][j];
            }
        }
        //if ((t%100) == 0) printf("interacao %d - diferenca=%g\n", t, difmedio/((N-2)*(N-2)));
    }
}

int main() {
    double **C = malloc(N * sizeof(double *));      // Concentração inicial
    double **C_new = malloc(N * sizeof(double *));  // Concentração para a próxima iteração
    FILE *tempos;
    if (C == NULL || C_new == NULL) {
        fprintf(stderr, "Erro ao alocar memória para as linhas\n");
        return 1;
    }

    for (int i = 0; i < N; i++) {
        C[i] = malloc(N * sizeof(double));
        C_new[i] = malloc(N * sizeof(double));
        if (C[i] == NULL || C_new[i] == NULL) {
            fprintf(stderr, "Erro ao alocar memória na linha %d\n", i);
            return 1;
        }
        memset(C[i], 0, N * sizeof(double));
        memset(C_new[i], 0, N * sizeof(double));
    }

    clock_t tempo;
    double temposReg[10];
    tempos = fopen("FinalOpenMP-Tempo.txt", "w");
    for (int k = 1; k <= 16;) {
        double mediaTempo = 0, desvioPadraoTempo = 0;
        for (int z = 0; z < 10; z++) {
            t = k;
            tempo = clock();

            // Inicializar uma concentração alta no centro
            C[N/2][N/2] = 1.0;

            // Executar a equação de difusão
            diff_eq(C, C_new);

            // Exibir resultado para verificação
            //printf("Concentracao final no centro: %f\n", C[N/2][N/2]);

            temposReg[z] = ((double)clock() - tempo)/CLOCKS_PER_SEC;
            //Ja vou somando a media aqui pois eu preciso dela para calcular o desvio padrao depois
            mediaTempo += temposReg[z];

            for (int j = 0; j < N; j++) {
                memset(C[j], 0, N * sizeof(double));
                memset(C_new[j], 0, N * sizeof(double));
            }
        }
        //Tratar das medidas estatísticas
        mediaTempo /= 10;
        for (int i = 0; i < 10; i++) {
            desvioPadraoTempo += pow((temposReg[i] - mediaTempo), 2);
        }
        desvioPadraoTempo /= 10;
        desvioPadraoTempo = sqrt(desvioPadraoTempo);
        fprintf(tempos, "%f %f\n", mediaTempo, desvioPadraoTempo);
        //Fazer com que o k seja o num_threads, e teste 1, 2, 4, 6, 8, 10, 12, 14 e 16 threads.
        if (k == 1) k *= 2;
        else k += 2;
    }

    fclose(tempos);
    // Liberar a memória alocada
    for (int i = 0; i < N; i++) {
        free(C[i]);
        free(C_new[i]);
    }
    free(C);
    free(C_new);

    return 0;
}