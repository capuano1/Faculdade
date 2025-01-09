#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define N 2000 // Tamanho da grade
int T = 2000; // Número de iterações
#define D 0.1 // Coeficiente de difusão
#define DELTA_T 0.01
#define DELTA_X 1.0
#define BLOCK_SIZE 16 // Threads per block -> no dim3 ele acaba fazendo dim3(x, y) = x*y threads, no caso, BLOCK_SIZE^2 threads.
// Ou seja, BLOCK_SIZE = sqrt(threads), vulgo, raiz quadrada do numero de threads
// Portanto, numero maximo seria 32, que vai dar 1024 threads

__global__ void calculateC(double* C, double* C_new) { 
    int i = blockIdx.y * blockDim.y + threadIdx.y + 1;
    int j = blockIdx.x * blockDim.x + threadIdx.x + 1;
    if (i < N - 1 && j < N - 1) {
        C_new[j + i * N] = C[j + i * N] + D * DELTA_T * (
            (C[j + 1 + i * N] + C[j - 1 + i * N] + C[j + (i + 1) * N] + C[j + (i - 1) * N] - 4 * C[j + i * N]) / (DELTA_X * DELTA_X) );
    }
}

__global__ void updateC(double* C, double* C_new, double* difmedio) {
    int i = blockIdx.y * blockDim.y + threadIdx.y + 1;
    int j = blockIdx.x * blockDim.x + threadIdx.x + 1;
    if (i < N - 1 && j < N - 1) {
        *difmedio += fabs(C_new[j + i * N] - C[j + i * N]);
        C[j + i * N] = C_new[j + i * N];
    }
}

void diff_eq(double* C, double* C_new) {
    double* d_C;
    double* d_C_new;
    double* d_difmedio;
    double difmedio;
    
    cudaMalloc(&d_C, N * N * sizeof(double));
    cudaMalloc(&d_C_new, N * N * sizeof(double));
    cudaMalloc(&d_difmedio, sizeof(double));

    cudaMemcpy(d_C, C, N * N * sizeof(double), cudaMemcpyHostToDevice);
    cudaMemcpy(d_C_new, C_new, N * N * sizeof(double), cudaMemcpyHostToDevice);

    dim3 blockSize(BLOCK_SIZE, BLOCK_SIZE);
    dim3 gridSize((N + BLOCK_SIZE - 1) / BLOCK_SIZE, (N + BLOCK_SIZE - 1) / BLOCK_SIZE);
    
    for (int t = 0; t < T; t++) {
        cudaMemset(d_difmedio, 0, sizeof(double));
        calculateC<<<gridSize, blockSize>>>(d_C, d_C_new);
        cudaDeviceSynchronize();
        updateC<<<gridSize, blockSize>>>(d_C, d_C_new, d_difmedio);
        cudaDeviceSynchronize();
        cudaMemcpy(&difmedio, d_difmedio, sizeof(double), cudaMemcpyDeviceToHost);
        /*if ((t % 100) == 0) {
            printf("interacao %d - diferenca=%g\n", t, difmedio / ((N - 2) * (N - 2)));
        }*/
    }
    
    cudaMemcpy(C, d_C, N * N * sizeof(double), cudaMemcpyDeviceToHost);
    cudaMemcpy(C_new, d_C_new, N * N * sizeof(double), cudaMemcpyDeviceToHost);
    cudaFree(d_C);
    cudaFree(d_C_new);
    cudaFree(d_difmedio);
}

int main() {
    double* C = (double*)malloc(N * N * sizeof(double)); // Concentração inicial
    double* C_new = (double*)malloc(N * N * sizeof(double)); // Concentração para a próxima iteração
    FILE *dados;
    
    if (C == NULL || C_new == NULL) {
        fprintf(stderr, "Erro ao alocar memória\n");
        return 1;
    }
    
    dados = fopen("FinalCUDA-DadosCompatibilidade.txt", "w");
    for (; T < 2100; T++) {
        memset(C, 0, N * N * sizeof(double));
        memset(C_new, 0, N * N * sizeof(double));
    
        // Inicializar uma concentração alta no centro
        C[N / 2 * N + N / 2] = 1.0;
    
        // Executar a equação de difusão
        diff_eq(C, C_new);
    
        // Exibir resultado para verificação
        fprintf(dados, "%f\n", C[N / 2 * N + N / 2]);
    }

    fclose(dados);

    // Liberar a memória alocada
    free(C);
    free(C_new);
    return 0;
}