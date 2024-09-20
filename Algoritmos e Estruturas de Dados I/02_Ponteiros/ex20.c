#include <stdio.h>

int negativos (float *, int);

int main (void) {
  int n, i;

  printf("Selecione o tamanho do seu array: ");
  scanf("%i", &n);

  float vet[n];

  for (i = 0; i < n; i++) {
    printf("Insira um número: ");
    scanf("%f", &vet[i]);
  }

  int neg = negativos(vet, n);
  
  printf("Este vetor possui %i números negativos\n", neg);
}

int negativos (float *vetor, int n) {
  int i, neg = 0;
  
  for (i = 0; i < n; i++) {
    if (vetor[i] < 0)
      neg++;
  }
  return neg;
}