#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main (void) {
  srand(time(NULL));
  int matriz[8][8], i, j;
  for (i = 0; i < 8; i++) {
    for (j = 0; j < 8; j++) {
      matriz[i][j] = rand()%101;
    }
  }
  for (i = 0; i < 8; i++) {
    for (j = 0; j < 8; j++) {
      if (i < j)
        matriz[i][j] = 0;
      printf("%i ", matriz[i][j]);
    }
    printf("\n");
  }
}