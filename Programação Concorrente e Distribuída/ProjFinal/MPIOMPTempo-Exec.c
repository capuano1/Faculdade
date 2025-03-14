#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

int main(int argc, char *argv[]) {
    FILE *tempos;
    double media = 0, dp = 0;
    double temposReg[10];
    for (int i = 0; i < 10; i++) {
        system("mpiexec -np 4 -genv I_MPI_PIN_DOMAIN=omp -genv OMP_NUM_THREADS=3 FinalMPIOMP-Tempo.exe");
    }
    tempos = fopen("FinalMPIOMP-Tempo.txt", "r");
    for (int i = 0; i < 10; i++) {
        fscanf(tempos, "%lf", &temposReg[i]);
        //printf("%f", temposReg[i]);
        media += temposReg[i];
    }
    media /= 10;
    for (int i = 0; i < 10; i++) {
        dp += pow((temposReg[i] - media), 2);
    }
    dp /= 10;
    dp = sqrt(dp);
    fclose(tempos);
    tempos = fopen("FinalMPIOMP-Tempo.txt", "w");
    fprintf(tempos, "%f %f", media, dp);
    fclose(tempos);
}