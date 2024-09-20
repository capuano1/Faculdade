#include <stdio.h>

int main(void) {
  #define max 10
  typedef int vetor[max];
  vetor R, S, X, Y = {0,0,0,0,0,0,0,0,0,0};
  int i, somaR, somaS;
  for (i = 0, somaR = 0; i < max; i++) {
    printf("Termo do vetor R: ");
    scanf("%i", &R[i]);
    somaR = somaR + R[i];
  }
  printf("Soma do vetor R: %i \n", somaR);
  for (i = 0, somaS = 0; i < max; i++) {
    printf("Termo do vetor S: ");
    scanf("%i", &S[i]);
    somaS = somaS + S[i];
  }
  printf("Soma do vetor S: %i \n", somaS);
  for (i = 0; i < max; i++) {
    X[i] = R[i] + S[i];
    printf("X[%i] = %i \n", i, X[i]);
  }
  for (i = 0; i < max; i++) {
    Y[i] = R[i] * S[i];
    printf("Y[%i] = %i \n", i, Y[i]);
  }
}