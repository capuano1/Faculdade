#include <stdio.h>

int main (void) {
  #define tamanho 10
  int i, soma, aux, A[tamanho];
  for (i = 0, soma = 0; i < tamanho; i++) {
    printf("Digite um número: ");
    scanf("%i", &aux);
    soma = soma + (aux * aux);
  }
  printf("Soma dos quadrados dos termos do vetor: %i", soma);
}