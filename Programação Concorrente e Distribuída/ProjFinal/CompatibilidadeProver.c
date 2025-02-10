#include <stdio.h>
#include <stdlib.h>

int main () {
    FILE *dadosSequencial, *dadosOpenMP, *dadosCUDA, *dadosMPI, *dadosMPIOMP;
    dadosOpenMP = fopen("FinalOpenMP-DadosCompatibilidade.txt", "r");
    dadosSequencial = fopen("FinalSequencial-DadosCompatibilidade.txt", "r");
    dadosCUDA = fopen("FinalCUDA-DadosCompatibilidade.txt", "r");
    dadosMPI = fopen("FinalMPI-DadosCompatibilidade.txt", "r");
    dadosMPIOMP = fopen("FinalMPIOMP-TestesComp.txt", "r");
    for (int i = 0; i < 100; i++) {
        double n, m, o, p, q;
        fscanf(dadosOpenMP, "%lf", &n);
        fscanf(dadosSequencial, "%lf", &m);
        fscanf(dadosCUDA, "%lf", &o);
        fscanf(dadosMPI, "%lf", &p);
        fscanf(dadosMPIOMP, "%lf", &q);
        //printf("%lf %lf\n", n, m);
        if (n != m || n != o || m != o || n != p || n != q) {printf("Error!"); return 0;}
    }
    fclose(dadosOpenMP);
    fclose(dadosSequencial);
    fclose(dadosCUDA);
    fclose(dadosMPI);
    fclose(dadosMPIOMP);
    printf("Compativel!");
}