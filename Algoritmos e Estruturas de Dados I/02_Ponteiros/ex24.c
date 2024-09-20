#include <stdio.h>

void minmax (int *, int *, int *, int);

int main (void) {
  int min, max, n, i;

  printf("Insira o tamanho do seu array: ");
  scanf("%i", &n);

  int vet[n];

  for (i = 0; i < n; i++) {
    printf("Insira um número: ");
    scanf("%i", &vet[i]);
  }
  
  min = vet[0];
  max = min;

  minmax(vet, &max, &min, n);

  printf("O número mínimo é %i e o máximo é %i\n", min, max);
}

void minmax (int *vetor, int *max, int *min, int n) {
  int i;

  for (i = 0; i < n; i++) {
    if (vetor[i] > *max)
      *max = vetor[i];
    else if (vetor[i] < *min)
      *min = vetor[i];
  }
}