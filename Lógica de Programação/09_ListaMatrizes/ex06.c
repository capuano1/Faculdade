#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX 20

int main (void) {
  srand(time(NULL));
  int matriz[MAX][MAX], i, j, n, cont = 0;
  for (i = 0; i < MAX; i++){
    for (j = 0; j < MAX; j++) {
      matriz[i][j] = rand()%101;
    }
  }
  printf("Digite o número a ser buscado: ");
  scanf("%i", &n);
  for (i = 0; i < MAX; i++){
    for (j = 0; j < MAX; j++) {
      if (n == matriz[i][j]) {
        printf("Posição [%i][%i]\n", i, j);
        cont++;
      }
    }
  }
  if (cont == 0)
    printf("Número não encontrado");
  else
    printf("Número encontrado %i vezes", cont);
}