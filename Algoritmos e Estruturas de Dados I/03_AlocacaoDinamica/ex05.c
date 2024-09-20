#include <stdio.h>
#include <stdlib.h>

typedef struct {
  /*Eu usei double pois quando fiz com int deu problema, foi para um número negativo,
  então assumi que eu havia ultrapassado o limite de valor de int.*/
  double CPF;
  char nome [100];
  int dataNasc[3];
} pessoa;

void preenPessoa (pessoa *);
void impPessoa (pessoa *);

int main (void) {
  pessoa *fulano;
  fulano = (pessoa *) malloc(sizeof(pessoa));
  preenPessoa (fulano);
  impPessoa (fulano);
  free (fulano);
}

void preenPessoa (pessoa *fulano) {
  printf("Qual é o seu nome?\n");
  fgets(fulano->nome, 100, stdin);
  printf("Qual é o seu CPF?\n");
  scanf("%lf", &fulano->CPF);
  printf("Quando você nasceu?\n");
  printf("Dia: ");
  scanf("%i", &fulano->dataNasc[0]);
  printf("Mês: ");
  scanf("%i", &fulano->dataNasc[1]);
  printf("Ano: ");
  scanf("%i", &fulano->dataNasc[2]);
}

void impPessoa (pessoa *fulano) {
  printf("Nome: %s", fulano->nome);
  printf("CPF: %.0lf\n", fulano->CPF);
  printf("Data de Nascimento: %i/%i/%i\n", fulano->dataNasc[0], fulano->dataNasc[1], fulano->dataNasc[2]);
}