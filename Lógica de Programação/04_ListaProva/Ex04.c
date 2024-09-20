#include <stdio.h>

float aumento (float sal, float percent) {
  return sal * ((percent / 100) + 1);
}

int main (void) {
  float sal, percent;
  scanf("%f", &sal);
  scanf("%f", &percent);
  printf("Novo salário: %.2f", aumento(sal, percent));
}