#include <stdio.h>

void divorcio (float, int *, float *);

int main(void) {
  float num, dec;
  int redondo;
  printf("Número: ");
  scanf("%f", &num);
  divorcio (num, &redondo, &dec);
  printf("Inteiro: %i\nFracionário: %.2f\n", redondo, dec);
}

void divorcio (float num, int *inteiro, float *frac) {
  *inteiro = (int)num;
  *frac = num - *inteiro;
}