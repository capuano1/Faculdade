#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
    char num[30];
    char comm[100];
    for (int i = 2000; i < 2100; i++) {
        sprintf(num, "%i", i);
        strcpy(comm, "mpiexec -np 8 FinalMPI-Dados.exe ");
        strcat(comm, num);
        system(comm);
    }
}