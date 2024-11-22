#include <stdio.h>
#include <stdlib.h>

int main () {
    FILE *dadosSequencial, *dadosOpenMP;
    dadosOpenMP = fopen("FinalOpenMP-DadosCompatibilidade.txt", "r");
    dadosSequencial = fopen("FinalSequencial-DadosCompatibilidade.txt", "r");
    for (int i = 0; i < 100; i++) {
        double n, m;
        fscanf(dadosOpenMP, "%lf", &n);
        fscanf(dadosSequencial, "%lf", &m);
        //printf("%lf %lf\n", n, m);
        if (n != m) {printf("Error!"); return 0;}
    }
    fclose(dadosOpenMP);
    fclose(dadosSequencial);
    printf("Compativel!");
}