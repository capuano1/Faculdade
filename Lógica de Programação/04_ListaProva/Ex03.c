#include <stdio.h>

int idDias (int anos, int meses, int dias) {
  return (anos * 365) + (meses * 30) + dias;
}

int main (void) {
  int dias, meses, anos;
  scanf("%i", &anos);
  scanf("%i", &meses);
  scanf("%i", &dias);
  printf("Idade em dias: %i", idDias(anos, meses, dias));
}