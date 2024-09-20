#include <stdio.h>

int primo (int num) {
  int i;
  for (i = 2; i < num; i++) {
    if (num % i == 0)
      return 0;
  }
  return 1;
}

int main (void) {
  int num;
  do {
    printf("Digite um número positivo maior que 1: ");
    scanf("%i", &num);
  }
  while (num < 2);
  if (primo(num) == 0)
    printf("Este número não é primo");
  else
    printf("Este número é primo");
}