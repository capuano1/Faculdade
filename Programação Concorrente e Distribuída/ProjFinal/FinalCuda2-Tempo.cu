#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define N 2000 // Tamanho da grade
#define T 2000 // Número de iterações
#define D 0.1 // Coeficiente de difusão
#define DELTA_T 0.01
#define DELTA_X 1.0
int BLOCK_SIZE = 0; // Threads per block -> no dim3 ele acaba fazendo dim3(x, y) = x*y threads, no caso, BLOCK_SIZE^2 threads.
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
    FILE *tempos;
    
    if (C == NULL || C_new == NULL) {
        fprintf(stderr, "Erro ao alocar memória\n");
        return 1;
    }
    

    clock_t tempo;
    double temposReg[10];
    tempos = fopen("FinalCUDA-Tempo.txt", "w");
    memset(C, 0, N * N * sizeof(double));
    memset(C_new, 0, N * N * sizeof(double));
    for (; BLOCK_SIZE <= 32; BLOCK_SIZE += 4) {
        if (BLOCK_SIZE == 0) BLOCK_SIZE++; //Para fazer com 1 thread apenas
        
        double mediaTempo = 0, desvioPadraoTempo = 0;
        for (int z = 0; z < 10; z++) {
            tempo = clock();
    
            // Inicializar uma concentração alta no centro
            C[N / 2 * N + N / 2] = 1.0;
    
            // Executar a equação de difusão
            diff_eq(C, C_new);

            temposReg[z] = ((double)clock() - tempo)/CLOCKS_PER_SEC;
            mediaTempo += temposReg[z];
            memset(C, 0, N * N * sizeof(double));
            memset(C_new, 0, N * N * sizeof(double));
        }
        mediaTempo /= 10;
        for (int i = 0; i < 10; i++) {
            desvioPadraoTempo += pow((temposReg[i] - mediaTempo), 2);
        }
        desvioPadraoTempo /= 10;
        desvioPadraoTempo = sqrt(desvioPadraoTempo);
        fprintf(tempos, "%f %f\n", mediaTempo, desvioPadraoTempo);
        if (BLOCK_SIZE == 1) BLOCK_SIZE--; //Para desfazer a iteracao de 1 thread, voltar para 0 e ir em incrementos de 4 ate 32
    }
    
    // Liberar a memória alocada
    free(C);
    free(C_new);
    printf("Tempo: %f segundos\n", ((double)clock() - tempo) / CLOCKS_PER_SEC);
    return 0;
}