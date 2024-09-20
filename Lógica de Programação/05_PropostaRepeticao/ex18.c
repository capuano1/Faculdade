#include <stdio.h>

int main (void) {
  int i, scan, num, min, max, soma;
  printf("Quantos números serão inseridos: ");
  scanf("%i", &num);
  soma = 0;
  max = 0;
  min = 0;
  for (i = 1; i <= num; i++) {
    printf("Num: ");
    scanf("%i", &scan);
    soma = soma + scan;
/* Devo fazer essa checagem pois, até aqui, min e max são 0, que eu defini acima para não pegar o lixo. Assim, o primeiro número inserido será sempre um ponto de partida.
*/
    if (i == 1) {
      max = scan;
      min = scan;
    }
    else {
      if (scan > max)
        max = scan;
      else
        min = scan;
    }
  }
  printf("O menor valor é %i, o maior é %i e a soma dos valores é %i", min, max, soma);
}