#include <stdio.h>
#include <omp.h>
#include <Windows.h>
#define max_threads 4
#define max_iterations 1000000

long soma = 0;
long long int iteration = 0;

void client (int id) {
    while(iteration < max_iterations) {
        //SC
        int localsum = soma;
        Sleep(rand()%2000);
        soma = localsum + 1;
        //Fim SC
        printf("ID: %d\tSoma: %d\n", id, soma);
        iteration++;
    }
}

int main () {
    #pragma omp parallel num_threads(max_threads)
    client(omp_get_thread_num());
}