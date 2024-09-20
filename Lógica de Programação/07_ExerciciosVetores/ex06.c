#include <stdio.h>

int main (void) {
  #define tamanho 5
  int i, soma, mult, vetor[tamanho];
  for (i = 0, soma = 0, mult = 1; i < tamanho; i++) {
    printf("Digite um número: ");
    scanf("%i", &vetor[i]);
    soma = soma + vetor[i];
    mult = mult * vetor[i];
  }
  for (i = 0; i < tamanho; i++) {
    printf("vetor[%i]: %i\n", i, vetor[i]);
  }
  printf("Soma = %i\nMultiplicação = %i\n", soma, mult);
}