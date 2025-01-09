/*
ABANDONADO E REESCRITO -> NOVO ARQUIVO: FinalCuda2.cu
Salvo por motivos de segurança, caso o outro jeito desse errado
*/

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define N 2000  // Tamanho da grade
#define B 256 //Quantos blocos
#define T 2000 // Número de iterações
#define D 0.1  // Coeficiente de difusão
#define DELTA_T 0.01
#define DELTA_X 1.0

__global__ void diff_eq(double* C, double* C_new) {
    for (int i = 1; i < N - 1; i++) {
        for (int j = 1; j < N - 1; j++) {
            C_new[j + (i*N)] = C[j + (i*N)] + D * DELTA_T * (
                (C[j+1 + (i*N)] + C[j-1 + (i*N)] + C[j + ((i+1)*N)] + C[j + ((i-1)*N)] - 4 * C[j + (i*N)]) / (DELTA_X * DELTA_X)
            );
        }
    }
    __syncthreads();
    //Separar em dois
    double difmedio = 0.;
    for (int i = 1; i < N - 1; i++) {
        for (int j = 1; j < N - 1; j++) {
            difmedio += fabs(C_new[j + (i*N)] - C[j + (i*N)]);
            C[j + (i*N)] = C_new[j + (i*N)];
        }
    }
    //if ((t%100) == 0) printf("interacao %d - diferenca=%g\n", t, difmedio/((N-2)*(N-2)));
    __syncthreads();
}

//Melhor a diff_eq ser a funcao que vai, no host, preparar tudo para o device e chamar as duas funcoes do device

int main() {
    double *C = (double*)malloc(N * N * sizeof(double));      // Concentração inicial
    double *C_new = (double*)malloc(N * N * sizeof(double));  // Concentração para a próxima iteração
    double *C_d;
    double *C_new_d;

    if (C == NULL || C_new == NULL) {
        fprintf(stderr, "Erro ao alocar memória para as linhas\n");
        return 1;
    }

    memset(C, 0, N * N * sizeof(double));
    memset(C_new, 0, N * N * sizeof(double));

    cudaMalloc((void**)&C_d, N*N*sizeof(double));
    cudaMalloc((void**)&C_new_d, N*N*sizeof(double));

    // Inicializar uma concentração alta no centro
    C[(N/2) + (N*(N/2))] = 1.0;

    cudaMemcpy(C_d, C, N * N * sizeof(double), cudaMemcpyHostToDevice);
    cudaMemcpy(C_new_d, C_new, N * N * sizeof(double), cudaMemcpyHostToDevice);

    clock_t tempo;
    tempo = clock();

    // Executar a equação de difusão
    // for mais externo foi puxado para cá pois ele não é paralelizavel
    for (int i = 0; i < T; i++) {
        diff_eq(C, C_new);
    }

    // Exibir resultado para verificação
    printf("Concentracao final no centro: %f\n", C[(N/2) + (N*(N/2))]);

    // Liberar a memória alocada
    free(C);
    free(C_new);
    cudaFree(C_d);
    cudaFree(C_new_d);

    printf("Tempo: %f segundos\n", ((double)clock() - tempo)/CLOCKS_PER_SEC);

    return 0;
}
