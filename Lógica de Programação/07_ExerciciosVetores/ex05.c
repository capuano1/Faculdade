#include <stdio.h>

int main (void) {
  #define tamanho 10
  int i, contador, localizador[tamanho];
  char con[tamanho];
  for (i = 0, contador = 0; i < tamanho; i++) {
    printf("Digite um caractere: ");
    scanf("%s", &con[i]);
    if (con[i] != 'a' && con[i] != 'A' && con[i] != 'e' && con[i] != 'E' && con[i] != 'i' && con[i] != 'I' && con[i] != 'o' && con[i] != 'O' && con[i] != 'u' && con[i] != 'U') {
      localizador[contador] = i;
      contador++;
    }
    else {
      continue;
    }
  }
  if (contador != 0) {
    printf("Temos %i consoante(s): ", contador);
    for (i = 0; i < contador; i++) {
      printf("%c", con[localizador[i]]);
    }
  }
  else {
    printf("Não foram identificadas consoantes");
  }
}