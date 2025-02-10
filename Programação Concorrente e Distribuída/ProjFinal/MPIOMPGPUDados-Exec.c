#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
    char num[30];
    char comm[500];
    for (int i = 2000; i < 2100; i++) {
        sprintf(num, "%i", i);
        strcpy(comm, "mpiexec -np 3 -genv I_MPI_PIN_DOMAIN=omp -genv OMP_NUM_THREADS=2 -genv I_MPI_OFFLOAD=1 FinalMPIOMPGPU-Dados.exe ");
        strcat(comm, num);
        system(comm);
    }
}