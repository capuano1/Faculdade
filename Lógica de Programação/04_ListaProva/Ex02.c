#include <stdio.h>

int area (int base, int altura) {
  return base * altura;
}


int main (void) {
  int base, altura;
  printf("\nBase: ");
  scanf("%i", &base);
  printf("\nAltura: ");
  scanf("%i", &altura);
  printf("\nÁrea do retângulo: %i", area(base, altura));
}