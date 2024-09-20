#include <stdio.h>

int main (void) {
  int fator, num;
  printf("Informe um número: ");
  scanf("%i", &fator);
  for (num = 1; fator >= 1; fator--) {
    num = fator * num;
  }
  printf("Seu fatorial é %i", num);
}