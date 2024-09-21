#include "Hanoi.h"

void inicializaPilhaHanoi (TipoPilha *pilha1, TipoPilha *pilha2, TipoPilha *pilha3) {
  pilha1->topo = NULL;
  pilha2->topo = NULL;
  pilha3->topo = NULL;
}

void destroiPilha (TipoPilha *pilha) {
  TipoNoh *ptrAux;
  if (!pilhaVazia(pilha)) {
    ptrAux = pilha->topo;
    while (ptrAux!=NULL) {
      pilha->topo = ptrAux->prox;
      free (ptrAux);
      ptrAux = pilha->topo;
    }
  }
}

int pilhaVazia (TipoPilha *pilha) {
  return pilha->topo == NULL;
}

int inicializaHanoi (TipoPilha *pilha1, int nDiscos) {
  int disco;
  
  for (disco = nDiscos; disco > 0; disco--) {
    TipoNoh *novoNoh;
    novoNoh = (TipoNoh*) malloc(sizeof(TipoNoh));
    if (novoNoh != NULL) {
      novoNoh->prox = pilha1->topo;
      pilha1->topo = novoNoh;
      novoNoh->disco.tamanho = disco;
    }
  }
  return 1;
}

int trocaPos (int src, int dst, TipoPilha *pilha1, TipoPilha *pilha2, TipoPilha *pilha3) {
  TipoNoh *ptrSrc, *ptrAux;
  if (!checaHanoi(src, dst, pilha1, pilha2, pilha3)) {
    return 0;
  }
  
  switch (src) {
    case 1:
      ptrSrc = pilha1->topo;
      ptrAux = ptrSrc->prox;
      pilha1->topo = ptrAux;
      break;

    case 2:
      ptrSrc = pilha2->topo;
      ptrAux = ptrSrc->prox;
      pilha2->topo = ptrAux;
      break;

    case 3:
      ptrSrc = pilha3->topo;
      ptrAux = ptrSrc->prox;
      pilha3->topo = ptrAux;
      break;
  }
  switch (dst) {
    case 1:
      ptrSrc->prox = pilha1->topo;
      pilha1->topo = ptrSrc;
      break;

    case 2:
      ptrSrc->prox = pilha2->topo;
      pilha1->topo = ptrSrc;
    break;

    case 3:
      ptrSrc->prox = pilha3->topo;
      pilha1->topo = ptrSrc;
    break;
  }
  return 1;
}

int checaHanoi (int src, int dst, TipoPilha *pilha1, TipoPilha *pilha2, TipoPilha *pilha3) {
  int disco1;
  int disco2;
  
  switch (src) {
    case 1:
      if (pilhaVazia(pilha1)) {
        disco1 = 0;
        break;
      }
      disco1 = pilha1->topo->disco.tamanho;
      break;

    case 2:
      if (pilhaVazia(pilha2)) {
        disco1 = 0;
        break;
      }
      disco1 = pilha2->topo->disco.tamanho;
      break;

    case 3:
      if (pilhaVazia(pilha3)) {
        disco1 = 0;
        break;
      }
      disco1 = pilha3->topo->disco.tamanho;
      break;
  }

  switch (dst) {
    case 1:
      if (pilhaVazia(pilha1)) {
        disco2 = 0;
        break;
      }
      disco2 = pilha1->topo->disco.tamanho;
      break;

    case 2:
      if (pilhaVazia(pilha2)) {
        disco2 = 0;
        break;
      }
      disco2 = pilha1->topo->disco.tamanho;
      break;

    case 3:
      if (pilhaVazia(pilha3)) {
        disco2 = 0;
        break;
      }
      disco2 = pilha3->topo->disco.tamanho;
      break;
  }
  printf("1:%i e 2:%i ", disco1, disco2);
  if (disco2 == 0)
    return 1;
  if (disco1 > disco2 || disco1 == 0)
    return 0;

  return 1;

}

int checaVitoria (TipoPilha *pilha3, int nDiscos) {
  TipoNoh *ptrAux;
  ptrAux = pilha3->topo;
  nDiscos--;
  while (ptrAux->prox != NULL) {
    nDiscos--;
  }
  if (nDiscos == 0)
    return 1;
  return 0;
}