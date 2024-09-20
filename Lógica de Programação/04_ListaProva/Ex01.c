#include <stdio.h>

int antecessor (int num) {
  return num - 1;
}

int main (void) {
  int num;
  printf("Número: ");
  scanf("%i", &num);
  printf("\nO antecessor é %i", antecessor(num));
}