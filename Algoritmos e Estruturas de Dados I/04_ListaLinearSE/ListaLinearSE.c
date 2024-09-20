#include "ListaLinearSE.h"

int listaVaziaLLSE(ListaLinearSE *lista){
  return lista->ultimo==0;
}

int listaCheiaLLSE(ListaLinearSE *lista){
  return lista->ultimo==MAX;
}

void inicializaLLSE(ListaLinearSE *lista){
  lista->ultimo = 0;
}

void destroiListaLLSE(ListaLinearSE *lista){
  lista->ultimo = 0;
}

void imprimeItem(TipoItem item){
  printf("%i %s\n",item.chave,item.nome);
}

void imprimeListaLLSE(ListaLinearSE *lista){
  int i;

  for(i=0;i<lista->ultimo;i++){
    imprimeItem(lista->itens[i]);
  }
}


int insereNoFinalLLSE(ListaLinearSE *lista, TipoItem novoItem){
  int pos = lista->ultimo;

  if(!listaCheiaLLSE(lista)){
    lista->itens[pos] = novoItem;
    lista->ultimo++;
    return 1;
  }
  else
    return 0;
}

int insereNaPosicao(ListaLinearSE *lista, TipoItem novoItem, int posDesejada) {
  int pos = lista->ultimo;
  int i;

  if (!listaCheiaLLSE(lista)) {
    for (i = pos; i > posDesejada; i--)
      lista->itens[i] = lista->itens[i-1];
    lista->itens[posDesejada] = novoItem;
    lista->ultimo++;
    return 1;
  }
  else
    return 0;
}

int insereNoInicioLLSE(ListaLinearSE *lista, TipoItem novoItem){
  int pos = lista->ultimo;
  int i;

  if(!listaCheiaLLSE(lista)){
    for(i=pos;i>0;i--)
      lista->itens[i] = lista->itens[i-1];
    lista->itens[0] = novoItem;
    lista->ultimo++;
    return 1;
  }
  else
    return 0;
}

int removeDoFinalLLSE(ListaLinearSE *lista,TipoItem *item){
  int pos = lista->ultimo;

  if(!listaVaziaLLSE(lista)){
    *item = lista->itens[pos-1];
    lista->ultimo--;
    return 1;
  }
  else
    return 0;
}

int removeDaPosicao (ListaLinearSE *lista, TipoItem *item, int posDesejada) {
  int pos = lista->ultimo;
  int i;

  if (!listaVaziaLLSE(lista)) {
    *item = lista->itens[posDesejada-1];
    for (i = posDesejada; i < pos-1; i++)
      lista->itens[i] = lista->itens[i+1];
    lista->ultimo--;
    return 1;
  }
  else
    return 0;
}

int removeEspecifico (ListaLinearSE *lista, TipoItem *item, int chaveBuscada) {
  int pos = lista->ultimo;
  int i, j;

  if (!listaVaziaLLSE(lista)) {
    for (i = 0; i < pos; i++) {
      if (lista->itens[i].chave == chaveBuscada) {
        *item = lista->itens[i];
        for (j = i; j < pos-1; j++)
          lista->itens[j] = lista->itens[j+1];
        lista->ultimo--;
        return 1;
      }
      else
        return 0;
    }
  }
  else
    return 0;
}

int removeDoInicioLLSE(ListaLinearSE *lista,TipoItem *item){
  int pos = lista->ultimo;
  int i;
  
  if(!listaVaziaLLSE(lista)){
    *item = lista->itens[0];
    for(i=1;i<pos;i++){
      lista->itens[i-1] = lista->itens[i];
    }
    lista->ultimo--;
    return 1;
  }
  else
    return 0;
}