#include <stdio.h>
#include <string.h>

int localizador (char texto[], char p1[], int i) {
  int aux;
  
  for (aux = i; aux < i + strlen(p1); aux++) {
    if (texto[aux] != p1[aux - i])
      return 0;
  }
  return 1;
}

void substitui (char texto[], char p1[], char p2[], int i) {
  int aux, dif;

  if (strlen(p1) == strlen(p2)) {
    for (aux = i; aux < i + strlen(p2); aux++) {
      texto[aux] = p2[aux - i];
    }
  }
  else if (strlen(p1) < strlen(p2)) {
    dif = strlen(p2) - strlen(p1);
    for (aux = strlen(texto); aux > i; aux--) {
      texto[aux + dif] = texto[aux];
    }
    for (aux = i; aux < i + strlen(p2); aux++) {
      texto[aux] = p2[aux - i];
    }
  }
  else {
    dif = strlen(p1) - strlen(p2);
    for (aux = i + strlen(p2); aux < strlen(texto); aux++) {
      texto[aux] = texto[aux + dif];
    }
    for (aux = i; aux < i + strlen(p2); aux++) {
      texto[aux] = p2[aux - i];
    }
  }
}

int main (void) {
  int i;
  char texto[100], p1[30], p2[30];
  
  printf("Digite o texto inicial: ");
  fgets(texto, sizeof(texto), stdin);
  texto[strlen(texto) - 1] = '\0';

  printf("Digite a palavra que será trocada: ");
  fgets(p1, sizeof(p1), stdin);
  p1[strlen(p1) - 1] = '\0';

  printf("Digite a nova palavra: ");
  fgets(p2, sizeof(p2), stdin);
  p2[strlen(p2) - 1] = '\0';

  for(i = 0; i < strlen(texto); i++) {
    if (texto[i] == p1[0])
      if (localizador(texto, p1, i))
        substitui(texto, p1, p2, i);
  }

  printf("Novo Texto: %s.\n", texto);
  return 0;
}