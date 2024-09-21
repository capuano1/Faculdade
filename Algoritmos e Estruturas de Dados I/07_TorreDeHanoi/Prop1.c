#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Hanoi.h"

int main(void) {
  TipoPilha pilha1, pilha2, pilha3;
  int nDiscos, movimentos, i, src, dst;

  inicializaPilhaHanoi (&pilha1, &pilha2, &pilha3);
  do {
    printf("Número de discos (1-%i): ", MAXDISK);
    scanf("%i", &nDiscos);
  }
  while (nDiscos < 1 || nDiscos > MAXDISK);
  inicializaHanoi (&pilha1, nDiscos);
  do {
    printf("Número de movimentos (1-%i): ", MAXPLAY);
    scanf("%i", &movimentos);
  }
  while (movimentos < 1 || movimentos > MAXPLAY);

  for (i = 0; i < movimentos; i++) {
    printf("Origem: ");
    scanf("%i", &src);
    printf("Destino: ");
    scanf("%i", &dst);
    if (!trocaPos(src, dst, &pilha1, &pilha2, &pilha3)) {
      printf("Movimento Inválido!");
      return 0;
    }
  }
  if (!checaVitoria(&pilha3, nDiscos)) {
    printf("Torre não Finalizada!");
    return 0;
  }
  printf("Você venceu!");
  return 1;
}