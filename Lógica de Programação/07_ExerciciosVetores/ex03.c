#include <stdio.h>

int main (void) {
  #define tamanho 10
  int i, vetor[tamanho];
  for (i = 0; i < tamanho; i++) {
    printf("Digite um número: ");
    scanf("%i", &vetor[i]);
  }
  for (i = tamanho - 1; i > -1; i--) {
    printf("vetor[%i]: %i\n", i, vetor[i]);
  }
}