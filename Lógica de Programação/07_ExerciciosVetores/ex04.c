#include <stdio.h>

int main (void) {
  #define tamanho 4
  int i, vetor[tamanho], media;
  for (i = 0, media = 0; i < tamanho; i++) {
    printf("Digite uma nota: ");
    scanf("%i", &vetor[i]);
    media = media + vetor[i];
  }
  media = media / tamanho;
  for (i = 0; i < tamanho; i++) 
    printf("Nota: %i\n", vetor[i]);
  printf("Média: %i", media);
}