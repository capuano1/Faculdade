#include <stdio.h>
#include <stdlib.h>

int contaCiclos (int vetor[], int tamanho) {
  int i, j, trocas = 0, visitado[300] = {0};
  int atual, ciclo;

  for (i = 0; i < tamanho; i++) {
    /* Checa se o elemento já está no lugar ou já foi verificado no ciclo */
    if (visitado[i] == 0 && vetor[i] != i) {
      ciclo = 0;
      atual = i;
      
      /* Percorre o ciclo até voltar ao inicio */
      while (visitado[atual] == 0) {
        visitado[atual] = 1;
        atual = vetor[atual];
        ciclo++;
      }
      
      if (ciclo > 0)
        trocas = trocas + (ciclo - 1);
    }
  }
  return trocas;
}

void resolve (int l, int c) {
  int i, j, valor, linDest, colDest, possivel = 1;
  int matriz[300][300];
  int mapaLin[300], mapaCol[300];
  // Inicializando os vetores de mapeamento com -1
  for (i = 0; i < l; i++) mapaLin[i] = -1;
  for (i = 0; i < c; i++) mapaCol[i] = -1;

  for (i = 0; i < l; i++) {
    for (j = 0; j < c; j++) {
      scanf("%i", &matriz[i][j]);
      
      // Calcula qual é o destino correto
      valor = matriz[i][j];
      linDest = (valor - 1) / c;
      colDest = (valor - 1) % c;

      // Checagem de conflito nas linhas, para ver se não tem dois elementos da mesma linha
      // querendo ir para linhas diferentes
      if (mapaLin[i] == -1)
        mapaLin[i] = linDest;
      else if (mapaLin[i] != linDest)
        possivel = 0;

      /* Mesma checagem para as colunas */
      if (mapaCol[j] == -1)
        mapaCol[j] = colDest;
      else if (mapaCol[j] != colDest)
        possivel = 0;
    }
  }

  // Garantir que não temos duas linhas ou colunas diferentes querendo ir para o mesmo lugar
  if (possivel == 1) {
      int checkL[300] = {0}, checkC[300] = {0};
      for (i = 0; i < l; i++) checkL[mapaLin[i]]++;
      for (i = 0; i < c; i++) checkC[mapaCol[i]]++;
      
      for (i = 0; i < l; i++) 
          if (checkL[i] != 1) possivel = 0;
      for (i = 0; i < c; i++) 
          if (checkC[i] != 1) possivel = 0;
  }

  if (possivel == 0) {
    printf("*\n");
  }
  else {
    // Calcula o total de trocas
    int total = contaCiclos(mapaLin, l) + contaCiclos(mapaCol, c);
    printf("%i\n", total);
  }
}

int main(void) {
  int l, c;
  while (scanf("%i %i", &l, &c) != EOF) {
    resolve(l, c);
  }
  return 0;
}