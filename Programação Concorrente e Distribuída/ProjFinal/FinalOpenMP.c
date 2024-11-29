#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <omp.h>

#define N 2000  // Tamanho da grade
#define T 2000 // Número de iterações
#define D 0.1  // Coeficiente de difusão
#define DELTA_T 0.01
#define DELTA_X 1.0

void diff_eq(double** C, double** C_new) {
    for (int t = 0; t < T; t++) {
        #pragma omp parallel for collapse(2) num_threads(4)
        for (int i = 1; i < N - 1; i++) {
            for (int j = 1; j < N - 1; j++) {
                C_new[i][j] = C[i][j] + D * DELTA_T * (
                    (C[i+1][j] + C[i-1][j] + C[i][j+1] + C[i][j-1] - 4 * C[i][j]) / (DELTA_X * DELTA_X)
                );
            }
        }
        double difmedio = 0.;
        #pragma omp parallel for collapse(2) num_threads(4) reduction(+:difmedio)
        for (int i = 1; i < N - 1; i++) {
            for (int j = 1; j < N - 1; j++) {
                difmedio += fabs(C_new[i][j] - C[i][j]);
                C[i][j] = C_new[i][j];
            }
        }
        if ((t%100) == 0) printf("interacao %d - diferenca=%g\n", t, difmedio/((N-2)*(N-2)));
    }
}

int main() {
    double **C = malloc(N * sizeof(double *));      // Concentração inicial
    double **C_new = malloc(N * sizeof(double *));  // Concentração para a próxima iteração
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
    tempo = clock();
    omp_set_dynamic(0);

    // Inicializar uma concentração alta no centro
    C[N/2][N/2] = 1.0;

    // Executar a equação de difusão
    diff_eq(C, C_new);

    // Exibir resultado para verificação
    printf("Concentracao final no centro: %f\n", C[N/2][N/2]);

    // Liberar a memória alocada
    for (int i = 0; i < N; i++) {
        free(C[i]);
        free(C_new[i]);
    }
    free(C);
    free(C_new);

    printf("Tempo: %f segundos\n", ((double)clock() - tempo)/CLOCKS_PER_SEC);

    return 0;
}
