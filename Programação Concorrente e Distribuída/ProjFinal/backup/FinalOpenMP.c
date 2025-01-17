#include <stdio.h>
#include <time.h>
#include <omp.h>
#define N 1000 // Tamanho da grade
#define T 1000 // Número de iterações
#define D 0.1 // Coeficiente de difusão
#define DELTA_T 0.01
#define DELTA_X 1.0

void diff_eq(double C[N][N], double C_new[N][N]) {
    int i, j;
    for (int t = 0; t < T; t++) {
        #pragma omp parallel for num_threads(16) private (i, j) shared(C, C_new) collapse(2)
        for (i = 1; i < N - 1; i++) {
            for (j = 1; j < N - 1; j++) {
                C_new[i][j] = C[i][j] + D * DELTA_T * ( (C[i+1][j] + C[i-1][j] + C[i][j+1] + C[i][j-1] - 4 * C[i][j]) / (DELTA_X * DELTA_X) );
            }
        }
        #pragma omp parallel for num_threads(4) private (i, j) shared(C, C_new) collapse(2)
        for (i = 1; i < N - 1; i++) {
            for (j = 1; j < N - 1; j++) {
                C[i][j] = C_new[i][j];
            }
        }
    }
}

int main() {
    double C[N][N] = {0}; // Concentração inicial
    double C_new[N][N] = {0}; // Concentração para a próxima iteração
    clock_t tempo;
    
    tempo = clock();
    // Inicializar uma concentração alta no centro
    C[N/2][N/2] = 25.0;
    // Executar a equação de difusão
    diff_eq(C, C_new);
    // Exibir resultado para verificação 
    printf("Concentração final no centro: %f\n", C[N/2][N/2]);
    printf("Tempo: %f", ((double)clock() - tempo)/CLOCKS_PER_SEC);
    return 0;
}