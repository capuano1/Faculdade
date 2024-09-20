#include <stdio.h>

int main (void) {
  int nota;
  nota = 0;
  do {
    if (nota != 0) {
      printf(" Valor Inválido! \n");
    }
    printf("\n Informe um valor entre 0 e 10: ");
    scanf("%i", &nota);
  }
  while (nota < 0 || nota > 10);
  printf("Nota: %i", nota);
}