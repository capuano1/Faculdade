#include <stdio.h>

int main (void) {
  int num1, num2, soma;
  printf("Digite o primeiro número: ");
  scanf("%i", &num1);
  printf("Digite o segundo número: ");
  scanf("%i", &num2);
  soma = 0;
  /* o if recebe +1 para que os intervalos com 1 de diferença entre os números caiam no else.
     o while recebe o +1 para que o número maior não seja impresso também, ou seja, para que ele pegue apenas o que há entre os dois números, sem incluir nenhum deles.
  */
  if (num1 > (num2 + 1)) {
    while (num1 > (num2 + 1)) {
      num2++;
      soma = soma + num2;
    }
    printf("%i", soma);
  }
  else if ((num1 + 1) < num2) {
    while ((num1 + 1) < num2) {
      num1++;
      soma = soma + num1;
    }
    printf("%i", soma);
  }
  else
    printf("Não há valores inteiros neste intervalo");
}