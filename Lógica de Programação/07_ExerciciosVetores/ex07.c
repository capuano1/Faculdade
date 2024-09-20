#include <stdio.h>

int main (void) {
  #define tamanho 5
  int i, idade[tamanho], altura[tamanho];
  for (i = 0; i < tamanho; i++) {
    printf("Idade pessoa %i: ", i+1);
    scanf("%i", &idade[i]);
    printf("Altura pessoa %i (em cm): ", i+1);
    scanf("%i", &altura[i]);
  }
  for (i = tamanho-1; i > -1; i--) {
    printf("Pessoa %i: Idade = %i e Altura = %i\n", i+1, idade[i], altura[i]);
  }
}