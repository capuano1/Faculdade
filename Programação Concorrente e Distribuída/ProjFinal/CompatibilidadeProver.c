#include <stdio.h>
#include <stdlib.h>

int main () {
    FILE *dadosSequencial, *dadosOpenMP, *dadosCUDA;
    dadosOpenMP = fopen("FinalOpenMP-DadosCompatibilidade.txt", "r");
    dadosSequencial = fopen("FinalSequencial-DadosCompatibilidade.txt", "r");
    dadosCUDA = fopen("FinalCUDA-DadosCompatibilidade.txt", "r");
    for (int i = 0; i < 100; i++) {
        double n, m, o;
        fscanf(dadosOpenMP, "%lf", &n);
        fscanf(dadosSequencial, "%lf", &m);
        fscanf(dadosCUDA, "%lf", &o);
        //printf("%lf %lf\n", n, m);
        if (n != m || n != o || m != o) {printf("Error!"); return 0;}
    }
    fclose(dadosOpenMP);
    fclose(dadosSequencial);
    fclose(dadosCUDA);
    printf("Compativel!");
}