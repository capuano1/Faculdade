#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main (void) {
  srand(time(NULL));
  int matriz [6][6], i, j, cont = 0;
  for (i = 0; i < 6; i++) {
    for (j = 0; j < 6; j++) {
      matriz[i][j] = rand()%26;
      if (matriz[i][j] > 10)
        cont++;
    }
  }
  printf("Esta matriz possui %i valores maiores que 10!", cont);
}