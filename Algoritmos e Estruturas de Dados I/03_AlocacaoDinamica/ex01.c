#include <stdio.h>
#include <stdlib.h>

void preenVet (int, int []);

int main(void) {
  int n, i;
  int *v;
  printf("Digite o tamanho do seu vetor: ");
  scanf("%i", &n);
  v = (int *) malloc(n * sizeof(int));
  preenVet(n, v);
  for (i = 0; i < n; i++) {
    printf("\nVetor[%i]: %i", i, v[i]);
  }
  free (v);
}

void preenVet (int n, int v[]) {
  int i;
  for (i = 0; i < n; i++) {
    printf("Digite o número de posição %i: ", i+1);
    scanf("%i", &v[i]);
  }
}