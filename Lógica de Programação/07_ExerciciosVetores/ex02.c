#include <stdio.h>

int main(void) {
  #define tamanho 5
  int i, vetor[tamanho];
  for (i = 0; i < tamanho; i++) {
    printf("Digite um número: ");
    scanf("%i", &vetor[i]);
  }
  for (i = 0; i < tamanho; i++) {
    printf("vetor[%i]: %i\n", i, vetor[i]);
  }
}