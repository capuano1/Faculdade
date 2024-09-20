#include <stdio.h>
#include <stdlib.h>

/*Não entendi muito bem o enunciado da 3, mas fiz simplesmente um programa que cria uma
matriz alocada dinamicamente em uma outra função e a retorna, para ser preenchida e
lida na função main.
*/

int **alocDynamic (int, int);

int main (void) {
  int i, j, m, n, choice;
  int **v;
  
  printf("Número de colunas desejado: ");
  scanf("%i", &m);
  printf("Número de linhas desejado: ");
  scanf("%i", &n);
  
  v = (int**)alocDynamic (m, n);

  for (i = 0; i < m; i++) {
    for (j = 0; j < n; j++) {
      printf("Posição [%i][%i]: ", i, j);
      scanf("%i", &v[i][j]);
    }
  }
  for (i = 0; i < m; i++) {
    for (j = 0; j < n; j++) {
      printf("\nPosição [%i][%i]: %i", i, j, v[i][j]);
    }
  }
  if (choice == 1)
    free(v);
}

int **alocDynamic (int m, int n) {
  int i;
  int **v;
  v = (int**)malloc(m * sizeof(int*));
  for (i = 0; i < m; i++) {
    v[i] = (int*)malloc(n * sizeof(int));
  }
  return v;
}