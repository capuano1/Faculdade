#include <stdio.h>

void abaixo();
void lado();

int main(void) {
  int escolha;
  printf("Escreva 1 para os números um abaixo do outro ou 0 para um ao lado do outro: ");
  scanf("%i", &escolha);
  if (escolha == 0)
    lado();
  else if (escolha == 1)
    abaixo();
   else
     main();
}

void abaixo() {
  int i;
  for (i = 1; i <= 20; i++) {
    printf("%i \n", i);
  }
}

void lado() {
  int i;
  for (i = 1; i <= 20; i++) {
    printf("%i ", i);
  }
}