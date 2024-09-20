#include <stdio.h>
#include <stdlib.h>

int localiza (int* array, int ini, int fim, int wally, int cont) {

  int centro = ini+(fim-ini)/2;
  
  if (ini == fim)
    return -1;
  
  if (array[centro] != wally) {
    cont++;
    if (wally > array[centro])
      return localiza(array, centro+1, fim, wally, cont);
    else
      return localiza(array, ini, centro-1, wally, cont);
  }
  else
    return cont;
  
}

int main() {
  int n, i, wally, result;
  int *array;

  scanf("%i", &n);
  array = malloc (n * sizeof(int));

  for (i=0; i < n; i++) {
    scanf("%i", &array[i]);
  }
  
  scanf("%i", &wally);

  n--;
  result = localiza(array, 0, n, wally, 0);

  if (result == -1)
    printf("%i nao foi encontrado", wally);
  else
    printf("%i", result);

  return 0;
}