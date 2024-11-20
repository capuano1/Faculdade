#include <stdio.h>
#include <stdbool.h>
#include <omp.h>
#include <Windows.h>
#define max_threads 5
#define max_iterations 1000000

int request, respond = 0;
long soma = 0;
long long int iteration = 0;

void client (int id) {
    while(iteration < max_iterations) {
        while (respond != id) request = id;
        //SC
        int localsum = soma;
        Sleep(rand()%2000);
        soma = localsum + 1;
        //Fim SC
        printf("ID: %d\tSoma: %d\n", id, soma);
        respond = 0;
        iteration++;
    }
}

void server (int id) {
    while(true) {
        while(request == 0)
        respond = request;
        while(respond != 0);
        request = 0;
    }
}

int main () {
    #pragma omp parallel num_threads(max_threads)
    if (omp_get_thread_num() == 0) server(0);
    else client(omp_get_thread_num());
}