#include <stdio.h>
#include <stdlib.h>

int * criaVetor(int);
void imprimeVetor(int *, int);
void liberaVetor(int *);

int main (void) {
  int n, i;
  int *v;

  printf("Tamanho desejado de vetor: ");
  scanf("%i", &n);
  v = criaVetor(n);
  for (i = 0; i < n; i++) {
    printf("Digite o elemento %i: ", i+1);
    scanf("%i", &v[i]);
  }
  imprimeVetor (v, n);
  liberaVetor (v);
}

int * criaVetor (int n) {
  int *v;
  
  v = (int *) malloc(n * sizeof(int));
  return v;
}

void imprimeVetor (int *v, int n) {
  int i;
  for (i = 0; i < n; i++) {
    printf("Elemento %i: %i\n", i+1, v[i]);
  }
}

void liberaVetor (int *v) {
  free(v);
}