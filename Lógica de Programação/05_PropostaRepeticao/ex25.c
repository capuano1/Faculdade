#include <stdio.h>

int main (void) {
  int i, idade, num, soma, media;
  printf("Número de pessoas entrevistadas: ");
  scanf("%i", &num);
  soma = 0;
  for (i = 1; i <= num; i++) {
    printf("Idade do entrevistado: ");
    scanf("%i", &idade);
    soma = soma + idade;
  }
  media = soma / num;
  if (media <= 25)
    printf("Em média, turma jovem");
  else if (media >= 26 && media <= 60)
    printf("Em média, turma adulta");
  else
    printf("Em média, turma idosa");
}