#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <C:\Program Files (x86)\Intel\oneAPI\compiler\2025.0\opt\compiler\include\omp.h>
#include <mpi.h>

#define N 2000  // Tamanho da grade
int T = 2000; // Número de iterações
#define D 0.1   // Coeficiente de difusão
#define DELTA_T 0.01
#define DELTA_X 1.0

void diff_eq(double **C, double **C_new, int first_row, int last_row, int rank, int size, MPI_Comm comm) {
    MPI_Request request[4];
    int num_requests = 0;

    for (int t = 0; t < T; t++) {
        num_requests = 0;

        if (rank > 0) {
            MPI_Isend(C[1], N, MPI_DOUBLE, rank - 1, 0, comm, &request[num_requests++]);
            MPI_Irecv(C[0], N, MPI_DOUBLE, rank - 1, 0, comm, &request[num_requests++]);
        }
        if (rank < size - 1) {
            MPI_Isend(C[last_row - first_row], N, MPI_DOUBLE, rank + 1, 0, comm, &request[num_requests++]);
            MPI_Irecv(C[last_row - first_row + 1], N, MPI_DOUBLE, rank + 1, 0, comm, &request[num_requests++]);
        }

        if (num_requests > 0) {
            MPI_Waitall(num_requests, request, MPI_STATUS_IGNORE);
        }

        #pragma omp parallel for collapse(2)
        for (int i = 1; i <= last_row - first_row; i++) {
            for (int j = 1; j < N - 1; j++) {
                C_new[i][j] = C[i][j] + D * DELTA_T * (
                    (C[i+1][j] + C[i-1][j] + C[i][j+1] + C[i][j-1] - 4 * C[i][j]) / (DELTA_X * DELTA_X)
                );
            }
        }

        double difmedio = 0.;
        #pragma omp parallel for collapse(2) reduction(+:difmedio)
        for (int i = 1; i <= last_row - first_row; i++) {
            for (int j = 1; j < N - 1; j++) {
                difmedio += fabs(C_new[i][j] - C[i][j]);
                C[i][j] = C_new[i][j];
            }
        }

        /*if ((t % 100) == 0 && rank == 0) {
            printf("interação %d - diferenca = %g\n", t, difmedio / ((N - 2) * (N - 2)));
        }*/
    }
}

void MPI(int argc, char *argv[]) {
    float result;
    FILE *dados;
    FILE *aux;
    MPI_Init(&argc, &argv);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int linhas_proc = N / size;
    int first_row = rank * linhas_proc;
    int last_row = (rank + 1) * linhas_proc - 1;

    if (rank == size - 1) {
        last_row = N - 1;
        linhas_proc = last_row - first_row + 1;
    }

    double **C = (double **)malloc((linhas_proc + 2) * sizeof(double *));
    double **C_new = (double **)malloc((linhas_proc + 2) * sizeof(double *));
    for (int i = 0; i < linhas_proc + 2; i++) {
        C[i] = calloc(N,sizeof(double));
        C_new[i] = calloc(N, sizeof(double));
    }

    if (rank == 0) {
        C[linhas_proc / 2][N / 2] = 1.0;
    }

    diff_eq(C, C_new, first_row, last_row, rank, size, MPI_COMM_WORLD);

    if (rank == 0) {
        result = C[linhas_proc / 2][N / 2];
        dados = fopen("FinalMPIOMP-TestesComp.txt", "r");
        aux = fopen("auxiliar.txt", "w");
        int c;
        while ((c = fgetc(dados)) != EOF) {
                fputc(c, aux);
        }
        fprintf(aux, "%f\n", result);
        fclose(dados);
        fclose(aux);
        dados = fopen("FinalMPIOMP-TestesComp.txt", "w");
        aux = fopen("auxiliar.txt", "r");
        while ((c = fgetc(aux)) != EOF) {
        fputc(c, dados);
        }
        fclose(dados);
        fclose(aux);  
    }

    for (int i = 0; i < linhas_proc + 2; i++) {
        free(C[i]);
        free(C_new[i]);
    }
    free(C);
    free(C_new);

    MPI_Finalize();

}

int main(int argc, char *argv[]) {
    printf("%i", argc);
    T = atoi(argv[argc-1]);
    MPI(argc, argv);

    //fprintf(dados, "%f\n", result);
    //fclose(dados);
    return 0;
}
