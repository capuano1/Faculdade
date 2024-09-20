#include <stdio.h>

void verifica(char ver){
  if (ver == 65 || ver == 69 || ver == 73 || ver == 79 || ver == 85)
    printf("Vogal");
  else
    printf("Consoante");
}

int main(void) {
  char letra;
  printf("Digite uma letra: ");
  scanf(" %c", &letra);
  verifica(letra);
  return 0;
}