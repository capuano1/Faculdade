#include <stdio.h>

int paridade (int num) {
  if (num % 2 == 0) {
    return 1;
  }
  else {
    return 0;
  }
}

int main(void) {
  int i, num, par = 0, impar = 0;
  for (i = 1; i <= 10; i++) {
    printf("Número: ");
    scanf("%i", &num);
    if (paridade(num) == 1)
      par++;
    else
      impar++;
  }
  printf("Você digitou %i números pares e %i números ímpares", par, impar);
}