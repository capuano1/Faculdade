#include "ListaLinearED.h"

int listaVaziaLLED(ListaLinearED *lista){
  return lista->ultimo==0;
}

void inicializaListaLLED(ListaLinearED *lista){
  lista->inicioLista = NULL;
  lista->ultimo = 0;
}

void destroiListaLLED(ListaLinearED* lista){
  TipoNoh *ptrAux1, *ptrAux2;
  if(!listaVaziaLLED(lista)){
    ptrAux1 = lista->inicioLista;
    ptrAux2 = ptrAux1->prox;
    while(ptrAux1->prox != NULL){
      free(ptrAux1);
      ptrAux1 = ptrAux2;
      ptrAux2 = ptrAux1->prox;
    }
    free(ptrAux1);
  }
  lista->inicioLista = NULL;
  lista->ultimo = 0;
}

void imprimeItemLLED(TipoItem item){
  printf("%i %s\n",item.chave,item.nome);
}

void imprimeListaLLED(ListaLinearED *lista){
  TipoNoh *ptrAux;
  if(!listaVaziaLLED(lista)){
    ptrAux = lista->inicioLista;
    while(ptrAux != NULL){
      imprimeItemLLED(ptrAux->item);
      ptrAux = ptrAux->prox;
    }
  }
}

int insereNoFinalLLED(ListaLinearED *lista,TipoItem item){
  TipoNoh *novoNoh, *ptrAux;
  novoNoh = (TipoNoh*) malloc(sizeof(TipoNoh));
  if(novoNoh != NULL){
    ptrAux = lista->inicioLista;
    if(!listaVaziaLLED(lista)){
      while(ptrAux->prox != NULL)
        ptrAux = ptrAux->prox;
      ptrAux->prox = novoNoh;
    }
    else{
      lista->inicioLista = novoNoh;
    }
    novoNoh->item = item;
    novoNoh->prox = NULL;
    lista->ultimo++;
    return 1;
  }
  return 0;
}

int insereNaPosicao(ListaLinearED *lista, TipoItem item, int posDesejada) {
  int i;
  TipoNoh *novoNoh, *ptrAux1, *ptrAux2;
  novoNoh = (TipoNoh*) malloc(sizeof(TipoNoh));
  if(novoNoh != NULL) {
    ptrAux1 = lista->inicioLista;
    ptrAux2 = ptrAux1->prox;
    if (ptrAux2 == NULL)
      return 0;
    else {
      for (i=1; i<posDesejada; i++) {
        ptrAux1 = ptrAux2;
        ptrAux2 = ptrAux1->prox;
        if (ptrAux2 == NULL)
          return 0;
      }
      novoNoh->item = item;
      novoNoh->prox = ptrAux2;
      ptrAux1->prox = novoNoh;
      lista->ultimo++;
      return 1;
    }
  }
  return 0;
}

int insereNoInicioLLED(ListaLinearED *lista,TipoItem item){
  TipoNoh *novoNoh;
  novoNoh = (TipoNoh*) malloc(sizeof(TipoNoh));
  if(novoNoh != NULL){
    novoNoh->item = item;
    novoNoh->prox = lista->inicioLista;
    lista->inicioLista = novoNoh;
    lista->ultimo++;
    return 1;
  }
  return 0;
}

int removeDoFinalLLED(ListaLinearED *lista,TipoItem *item){
  TipoNoh *ptrAux1, *ptrAux2;
  if(!listaVaziaLLED(lista)){
    ptrAux1 = lista->inicioLista;
    ptrAux2 = ptrAux1->prox;
    if(ptrAux2 == NULL){
      lista->inicioLista = NULL;
      *item = ptrAux1->item;
      free(ptrAux1);
    }
    else{
      while(ptrAux2->prox != NULL){
        ptrAux1 = ptrAux2;
        ptrAux2 = ptrAux2->prox;
      }
      ptrAux1->prox = NULL;
      *item = ptrAux2->item;
      free(ptrAux2);
    }
    lista->ultimo--;
    return 1;
  }
  return 0;
}

int removeEspecifico (ListaLinearED *lista, TipoItem *item, int chaveDesejada) {
  int i, j;
  TipoNoh *ptrAux1, *ptrAux2;
  if (!listaVaziaLLED(lista)) {
    ptrAux1 = lista->inicioLista;
    ptrAux2 = ptrAux1->prox;
    if (ptrAux1->item.chave == chaveDesejada || ptrAux2->item.chave == chaveDesejada) {
      if (ptrAux1->item.chave == chaveDesejada)
        removeDoInicioLLED (lista, item);
      else
        removeDaPosicao (lista, item, 1);
      return 1;
    }
    else {
      i = 1;
      do {
        i++;
        ptrAux1 = ptrAux2;
        ptrAux2 = ptrAux1->prox;
        if (ptrAux2->item.chave == chaveDesejada) {
          removeDaPosicao (lista, item, i);
          return 1;
        }
      }
      while (ptrAux2 != NULL);
    }
  }
  return 0;
}

int removeDaPosicao(ListaLinearED *lista, TipoItem *item, int posDesejada) {
  int i;
  TipoNoh *ptrAux1, *ptrAux2;
  if (!listaVaziaLLED(lista)) {
    ptrAux1 = lista->inicioLista;
    ptrAux2 = ptrAux1->prox;
    for (i = 1; i < posDesejada; i++) {
      ptrAux1 = ptrAux2;
      ptrAux2 = ptrAux1->prox;
    }
    ptrAux1->prox = ptrAux2->prox;
    *item = ptrAux2->item;
    free(ptrAux2);
    lista->ultimo--;
    return 1;
  }
  return 0;
}

int removeDoInicioLLED(ListaLinearED *lista, TipoItem *item){
  TipoNoh *ptrAux;
  if(!listaVaziaLLED(lista)){
    ptrAux = lista->inicioLista;
    *item = ptrAux->item;
    lista->inicioLista = ptrAux->prox;
    free(ptrAux);
    lista->ultimo--;
    return 1;
  }
  return 0;
}