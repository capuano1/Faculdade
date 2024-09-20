#include <stdio.h>

int main(void) {
  int n1 = 0, n2 = 1, prox = 1;
  printf("Fibonacci até 500: %i %i ", n1, n2);
  do {
    printf("%i ", prox);
    n1 = n2;
    n2 = prox;
    prox = n1 + n2;
  }
  while (prox < 500);
}