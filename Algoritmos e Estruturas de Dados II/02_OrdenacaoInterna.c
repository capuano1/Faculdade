#include <stdio.h>
#include <stdlib.h>

int* sort (int* array, int n) {
  int i, j, aux;
  
  for (i=0; i < n-1; i++)
    for (j=0; j < n-1-i; j++)
      if (array[j] > array[j+1]) {
        aux = array[j];
        array[j] = array[j+1];
        array[j+1] = aux;
      }
  return array;
}

int result (int* microrg, int* pot, int n) {
  int i;

  for (i=0; i < n; i++) {
    if (microrg[i] > pot[i])
      return 0;
  }
  return 1;
}

int main(void) {
  int n, i;
  int *microrg, *pot;

  scanf("%i", &n);

  microrg = malloc(n*sizeof(int));
  pot = malloc(n*sizeof(int));
  
  for (i=0; i < n; i++)
    scanf("%i", &microrg[i]);
  for (i=0; i < n; i++)
    scanf("%i", &pot[i]);

  microrg = sort(microrg, n);
  pot = sort(pot, n);

  if (result(microrg, pot, n) == 0)
    printf("nao");
  else
    printf("sim");

  free(microrg);
  free(pot);

  return 0;
  
}