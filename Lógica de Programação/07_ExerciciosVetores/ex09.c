#include <stdio.h>
#define max 50

int main(void) {
  float notas[max], nota = 1, soma = 0, media = 0;
  int i, n = 0, acimedia = 0, abaisete = 0;
  do {
    printf("Digite uma nota: ");
    scanf("%f", &nota);
  }
  while (nota > 10 || (nota < 0 && nota != -1));
  for (i = 0; nota != -1; i++) {
    soma = soma + nota;
    notas[i] = nota;
    if (nota < 7)
      abaisete++;
    do {
      printf("Digite uma nota: ");
      scanf("%f", &nota);
    }
    while (nota > 10 || (nota < 0 && nota != -1));
  }
  n = i;
  if (n == 0) {
    printf("Não é possível executar o programa sem notas!\n");
    main();
    return 0;
  }
  media = soma / n;
  printf("Quantidade de notas lidas: %i", i);
  printf("\nNotas na ordem que foram lidas: ");
  for (i = 0; i < n; i++) {
    printf("%.2f ", notas[i]);
  }
  printf("\nNotas na ordem inversa:\n");
  for (i = n-1; i > -1; i--) {
    printf("%.2f\n", notas[i]);
  }
  printf("Soma das notas: %.2f\n", soma);
  printf("Média das notas: %.2f\n", media);
  for (i = 0; i < n; i++) {
    if (notas[i] > media)
      acimedia++;
    else
      continue;
  }
  printf("Houveram %i notas acima da média da sala\n", acimedia);
  printf("Houveram %i notas abaixo de 7\n", abaisete);
  printf("Este é o fim do programa. Espero tirar 10 nesta atividade. Obrigado professora!");
}