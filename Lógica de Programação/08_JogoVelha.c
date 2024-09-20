#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void mostraCheca (int jogo[3][3], int modo, int jogador);

void ia (int jogo[3][3]) {
  srand(time(NULL));
  int i, j;
  do {
    i = rand() % 3;
    j = rand() % 3;
  }
  while (jogo[i][j] != 0);
  jogo[i][j] = 2;
  mostraCheca(jogo, 1, 2);
}

void game (int jogo[3][3], int jogador, int pc) {
  int lin, col;
  if (jogador == 1)
    jogador = 2;
  else
    jogador = 1;
  printf("Vez do jogador %i\n\n", jogador);
  if (pc == 1 && jogador == 2)
    ia(jogo);
  else {
    do {
      printf("Selecione uma linha (1-3): ");
      scanf("%i", &lin);
      printf("Selecione uma coluna (1-3): ");
      scanf("%i", &col);
      printf("\n");
    }
    while (jogo[lin-1][col-1] != 0);
    jogo[lin-1][col-1] = jogador;
    mostraCheca(jogo, pc, jogador);
  }
}

void mostraCheca (int jogo[3][3], int pc, int jogador) {
  int i, j, chec = 0;
  for (i = 0; i < 3; i++) {
    for (j = 0; j < 3; j++) {
      printf("%i\t", jogo[i][j]);
      if (jogo[i][j] == 0)
        chec++;
    }
    printf("\n\n\n");
  }
  /*Aqui é feita a checagem de vitória, nas diagonais, verticais e horizontais,
  além de checar se os números que estão sendo checados são diferentes de -1. */
  if ((jogo[0][0] != 0 && jogo[0][0] == jogo[1][1] && jogo[1][1] == jogo[2][2]) || (jogo[2][0] != 0  && jogo[2][0] == jogo[1][1] && jogo[1][1] == jogo[0][2]) || (jogo[0][0] != 0  && jogo[0][0] == jogo[0][1] && jogo[0][1] == jogo[0][2]) || (jogo[1][0] != 0  && jogo[1][0] == jogo[1][1] && jogo[1][1] == jogo[1][2]) || (jogo[2][0] != 0  && jogo[2][0] == jogo[2][1] && jogo[2][1] == jogo[2][2]) || (jogo[0][0] != 0  && jogo[0][0] == jogo[1][0] && jogo[1][0] == jogo[2][0]) || (jogo[0][1] != 0  && jogo[0][1] == jogo[1][1] && jogo[1][1] == jogo[2][1]) || (jogo[0][2] != 0  && jogo[0][2] == jogo[1][2] && jogo[1][2] == jogo[2][2])) {
    if (pc == 1) {
      if (jogador == 1)
        printf("Você venceu o computador!");
      else
        printf("Vitória do computador!");
    }
    else {
      if (jogador == 1)
        printf("O Jogador 1 vence!");
      else
        printf("O Jogador 2 vence!");
    }
  }
  /* Vamos checar se dá velha (empate). Já aproveitei para usar o for acima, que eu
  uso para mostrar o jogo, para checar se há alguma lacuna vazia. Estou fazendo esta
  checagem agora, após checar se há alguma vitória, pois há a possibilidade da
  última jogada acabar sendo a decisiva */
  else if (chec == 0)
    printf("O jogo empatou! Deu velha!");
  else
    game (jogo, jogador, pc);
}

int main(void) {
  int modo, i, jogo[3][3] = {0,0,0,0,0,0,0,0,0}, jogador = 2;
  do {
    printf("Modo de jogo (1 para jogar contra o computador, 2 para 2 jogadores): ");
    scanf("%i", &modo);
  }
  while (modo != 1 && modo != 2);
  if (modo == 1)
    printf("Você selecionou jogar contra o computador\n\n");
  else
    printf("Você selecionou o modo de 2 jogadores\n\n");
  printf("0\t0\t0\n\n\n0\t0\t0\n\n\n0\t0\t0\n\n\n");
  if (modo == 1)
    game(jogo, jogador, 1);
  else
    game(jogo, jogador, 0);
}

