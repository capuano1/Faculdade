#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Implementação: A matriz nos indica qual estado devo ir, considerando o estado que estou:
Dessa forma, vamos dizer que o estado atual é 2 e lemos 0, então temos matriz[2][0], que
nos dará o respectivo estado de destino. Com isso, fazemos um if para verificar se o estado
é aceito pelo DFA ou não.
*/

int binDivByTwo () {
  /*Essa implementação poderia ser mais simples, tendo em vista que para o binário ser
  divisível por 2, basta que o último bit seja 0. Porém, a fim de demonstrar o cálculo
  solicitado (simular equações delta chapéu), decidi fazer a implementação dessa maneira
  iterativa, que segue o mesmo padrão das outras funções.
  */
  int matrix[2][2] = {{0, 1}, {0, 1}};
  int state = 0;
  char string[32];
  printf("String: ");
  scanf("%s", string);
  
  for (int i = 0; i < strlen(string); i++) {
    //aux transforma ASCII em inteiro
    int aux = string[i] - 48;
    if (aux != 0 && aux != 1) return 1;
    state = matrix[state][aux];
  }
  return state;
}

int binDivByFive () {
  int matrix[5][2] = {{0, 1}, {2, 3}, {4, 0}, {1, 2}, {3, 4}};
  int state = 0;
  char string[32];
  printf("String: ");
  scanf("%s", string);

  for (int i = 0; i < strlen(string); i++) {
    //aux transforma ASCII em inteiro
    int aux = string[i] - 48;
    if (aux != 0 && aux != 1) return 1;
    state = matrix[state][aux];
  }
  return state;
}

int pairs () {
  int matrix[4][2] = {{1, 2}, {0, 3}, {3, 0}, {2, 1}};
  int state = 0;
  char string[32];
  printf("String: ");
  scanf("%s", string);

  for (int i = 0; i < strlen(string); i++) {
    //aux transforma ASCII em inteiro
    int aux = string[i] - 48;
    if (aux != 0 && aux != 1) return 1;
    state = matrix[state][aux];
  }
  return state;
}

int sameVariability () {
  int matrix[5][2] = {{1, 3}, {1, 2}, {1, 2}, {4, 3}, {4, 3}};
  int state = 0;
  char string[32];
  printf("String: ");
  scanf("%s", string);

  for (int i = 0; i < strlen(string); i++) {
    //aux transforma ASCII em inteiro
    int aux = string[i] - 48;
    if (aux != 0 && aux != 1) return 1;
    state = matrix[state][aux];
  }
  return state;
}

int fourZeros () {
  int matrix[6][2] = {{1, 0}, {2, 1}, {3, 2}, {4, 3}, {5, 4}, {5, 5}};
  int state = 0;
  char string[32];
  printf("String: ");
  scanf("%s", string);

  for (int i = 0; i < strlen(string); i++) {
    //aux transforma ASCII em inteiro
    int aux = string[i] - 48;
    if (aux != 0 && aux != 1) return 1;
    state = matrix[state][aux];
  }
  return state;
}

int specialEnding () {
  int matrix[5][2] = {{0, 1}, {0, 2}, {3, 2}, {0, 4}, {0, 2}};
  int state = 0;
  char string[32];
  printf("String: ");
  scanf("%s", string);

  for (int i = 0; i < strlen(string); i++) {
    //aux transforma ASCII em inteiro
    int aux = string[i] - 48;
    if (aux != 0 && aux != 1) return 1;
    state = matrix[state][aux];
  }
  return state;
}

int fourZerosTwoOnes () {
  int matrix[16][2] = {{1, 5}, {2, 6}, {3, 7}, {4, 8}, {15, 9},
                       {6, 10}, {7, 11}, {8, 12}, {9, 13}, {15, 14},
                       {11, 10}, {12, 11}, {13, 12}, {14, 13}, {15, 14},
                       {15, 15}};
  int state = 0;
  char string[32];
  printf("String: ");
  scanf("%s", string);

  for (int i = 0; i < strlen(string); i++) {
    //aux transforma ASCII em inteiro
    int aux = string[i] - 48;
    if (aux != 0 && aux != 1) return 1;
    state = matrix[state][aux];
  }
  return state;
}

int substring () {
  int matrix[5][2] = {{1, 0}, {1, 2}, {3, 0}, {1, 4}, {4, 4}};
  int state = 0;
  char string[32];
  printf("String: ");
  scanf("%s", string);

  for (int i = 0; i < strlen(string); i++) {
    //aux transforma ASCII em inteiro
    int aux = string[i] - 48;
    if (aux != 0 && aux != 1) return 1;
    state = matrix[state][aux];
  }
  return state;
}

int evenOrOdd () {
  int matrix[5][2] = {{1, 3}, {2, 2}, {1, 1}, {4, 4}, {3, 3}};
  int state = 0;
  char string[32];
  printf("String: ");
  scanf("%s", string);

  for (int i = 0; i < strlen(string); i++) {
    //aux transforma ASCII em inteiro
    int aux = string[i] - 48;
    if (aux != 0 && aux != 1) return 1;
    state = matrix[state][aux];
  }
  return state;
}

int notSubstring () {
  int matrix[4][2] = {{0, 1}, {0, 2}, {3, 2}, {3, 3}};
  int state = 0;
  char string[32];
  printf("String: ");
  scanf("%s", string);

  for (int i = 0; i < strlen(string); i++) {
    //aux transforma ASCII em inteiro
    int aux = string[i] - 48;
    if (aux != 0 && aux != 1) return 1;
    state = matrix[state][aux];
  }
  return state;
}

int sizeLessThanFive () {
  int matrix[7][2] = {{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {6, 6}};
  int state = 0;
  char string[32];
  printf("String: ");
  scanf("%s", string);

  for (int i = 0; i < strlen(string); i++) {
    //aux transforma ASCII em inteiro
    int aux = string[i] - 48;
    if (aux != 0 && aux != 1) return 1;
    state = matrix[state][aux];
  }
  return state;
}

int oddOne () {
  int matrix[3][2] = {{2, 1}, {0, 0}, {2, 2}};
  int state = 0;
  char string[32];
  printf("String: ");
  scanf("%s", string);

  for (int i = 0; i < strlen(string); i++) {
    //aux transforma ASCII em inteiro
    int aux = string[i] - 48;
    if (aux != 0 && aux != 1) return 1;
    state = matrix[state][aux];
  }
  return state;
}

int personalized () {
  int numOfStates, aux, numOfAccepted;
  
  printf("\nEntendo, nenhuma das opções lhe satisfez...\n");
  printf("Vamos criar uma então!\n");
  printf("Digite o número de estados desejados: ");
  scanf("%i", &numOfStates);

  int matrix [numOfStates][2];

  printf("Agora, vamos preencher a matriz dos casos!\n");
  for (int i = 0; i < numOfStates; i++) {
    for (int j = 0; j < 2; j++) {
      printf("Digite o resultado de estar no caso %i e ler %i: ", i, j);
      scanf("%i", &aux);
      matrix[i][j] = aux;
    }
  }
  do {
  printf("Agora, digite o número de estados aceitos (maior do que 0): ");
  scanf("%i", &numOfAccepted);
  } while (numOfAccepted < 1);
  int acceptedCases[numOfAccepted];
  printf("Agora, escreva quais são os casos aceitos, separados por espaço: ");
  for (int i = 0; i < numOfAccepted; i++) {
    scanf("%d", &acceptedCases[i]);
  }

  printf("Beleza, agora vamos testar a(s) string(s) desejada(s)!\n");
  printf("Quando você quiser sair dessa função, digite -1\n");
  char string[32];
  int state;
  
  while(1) {
    start:
    state = 0;
    printf("Digite a sua string: ");
    scanf("%s", string);
    if (strcmp(string, "-1") == 0) return 0;
    for (int i = 0; i < strlen(string); i++) {
      //aux transforma ASCII em inteiro
      int aux = string[i] - 48;
      if (aux != 0 && aux != 1) {
        printf("String rejeitada pelo DFA\n");
        break;
      }
      state = matrix[state][aux];
    }
    for (int i = 0; i < numOfAccepted; i++) {
      if (state == acceptedCases[i]) {
        printf("String aceita pelo DFA\n");
        goto start;
      }
    }
    printf("String rejeitada pelo DFA\n");
  }
}

int main (void) {
  int selection, aux;

  printf("PROJETO 02 EXTRA\n");
  printf("Linguagens Formais e Autômatos\n");
  printf("Programa para avaliar se uma string é aceita pelos DFAs implementados\n");
  printf("by Thiago Corso Capuano (Caputino)\n\n");
  printf("Alfabeto aceito: 1 e 0 apenas\n");
  
  do {
    printf("\nSelecione uma opção:\n");
    printf("1 - String com binário divisível por 2\n");
    printf("2 - String com binário divisível por 5\n");
    printf("3 - String com número par de 0s e 1s\n");
    printf("4 - String com mesmo número de 01 e 10\n");
    printf("5 - String com exatamente quatro 0s\n");
    printf("6 - String terminada em 1101\n");
    printf("7 - String com exatamente quatro 0s e ao menos dois 1s\n");
    printf("8 - String que contenha a substring 0101\n");
    printf("9 - String que começa com 0 e possui comprimento ímpar ou começa com 1 e possui comprimento par\n");
    printf("10 - String que não possua a substring 110\n");
    printf("11 - Strings de tamanho menor ou igual a 5\n");
    printf("12 - String que possua 1 em todas as posições ímpares\n");
    printf("13 - Caso personalizado\n");
    printf("0 - Sair\n");
    printf("Opção: ");
    
    scanf("%i", &selection);
    switch (selection) {
      case 0:
        return 0;
        break;
      case 1:
        if (!binDivByTwo()) printf("String aceita pelo DFA\n");
        else printf("String rejeitada pelo DFA\n");
        break;
      case 2:
        if (binDivByFive() == 0) printf("String aceita pelo DFA\n");
        else printf("String rejeitada pelo DFA\n");
        break;
      case 3:
        if (pairs() == 0) printf("String aceita pelo DFA\n");
        else printf("String rejeitada pelo DFA\n");
        break;
      case 4:
        aux = sameVariability();
        if (aux == 0 || aux == 1 || aux == 3) printf("String aceita pelo DFA\n");
        else printf("String rejeitada pelo DFA\n");
        break;
      case 5:
        if (fourZeros() == 4) printf("String aceita pelo DFA\n");
        else printf("String rejeitada pelo DFA\n");
        break;
      case 6:
        if (specialEnding() == 4) printf("String aceita pelo DFA\n");
        else printf("String rejeitada pelo DFA\n");
        break;
      case 7:
        if (fourZerosTwoOnes() == 14) printf("String aceita pelo DFA\n");
        else printf("String rejeitada pelo DFA\n");
        break;
      case 8:
        if (substring() == 4) printf("String aceita pelo DFA\n");
        else printf("String rejeitada pelo DFA\n");
        break;
      case 9:
        aux = evenOrOdd();
        if (aux == 1 || aux == 4) printf("String aceita pelo DFA\n");
        else printf("String rejeitada pelo DFA\n");
        break;
      case 10:
        if (notSubstring() != 3) printf("String aceita pelo DFA\n");
        else printf("String rejeitada pelo DFA\n");
        break;
      case 11:
        if (sizeLessThanFive() != 6) printf("String aceita pelo DFA\n");
        else printf("String rejeitada pelo DFA\n");
        break;
      case 12:
        if (oddOne() == 0) printf("String aceita pelo DFA\n");
        else printf("String rejeitada pelo DFA\n");
        break;
      case 13:
        personalized();
        break;
    }
  } while (selection != 0);
  return 0;
}