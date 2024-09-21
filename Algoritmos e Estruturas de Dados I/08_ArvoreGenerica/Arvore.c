#include "Arvore.h"

//Funções Lista
int listaVazia(TipoLista lista){
  return lista==NULL;
}

TipoLista inicializaLista(TipoLista lista){
  return NULL;
}

TipoLista destroiLista(TipoLista lista){
  TipoNoh *ptrAux;
  if(lista!=NULL){
    lista->prox = destroiLista(lista->prox);
    destroiArvore(lista->item);
  }
  return NULL;
}

TipoLista insereNoFinal(TipoLista lista,TipoItem item){
  TipoNoh *novoNoh;
  if(lista==NULL){
    novoNoh = (TipoNoh *) malloc(sizeof(TipoNoh));
    novoNoh->item = item;
    novoNoh->prox = NULL;
    return novoNoh;
  }
  else{
    lista->prox = insereNoFinal(lista->prox,item);
    return lista;
  }
}

TipoLista insereNoInicio(TipoLista lista,TipoItem item){
  TipoNoh *novoNoh;
  novoNoh = (TipoNoh *) malloc(sizeof(TipoNoh));
  novoNoh->item = item;
  novoNoh->prox = lista;
  return novoNoh;
}

TipoLista removeDoFinal(TipoLista lista,TipoItem *item){
  if(lista!=NULL){
    if(lista->prox==NULL){
      *item = lista->item;
      free(lista);
      return NULL;
    }
    else{
      lista->prox = removeDoFinal(lista->prox,item);
      return lista;
    }
  }
  return NULL;
}

TipoLista removeDoInicio(TipoLista lista,TipoItem *item){
  TipoNoh *ptrAux;
  if(lista!=NULL){
    ptrAux = lista;
    lista = lista->prox;
    *item = ptrAux->item;
    free(ptrAux);
    return lista;
  }
  return NULL;
}

void imprimeLista(TipoLista lista,int n){
  if(lista!=NULL){
    imprimeArvore(lista->item,n);
    imprimeLista(lista->prox,n);
  }
}

void imprimeListaAninhado (TipoLista lista, int n, int m) {
  n = 0;
  if(lista!=NULL) {
    if (lista->prox == NULL) {
      imprimeParAninhado(lista->item,0, 1);
      printf(")");
      m = 1;
    }
    else {
      imprimeParAninhado(lista->item,1, 0);
    }
    imprimeListaAninhado(lista->prox,n, 0);
  }
}


//Funções da Árvore
int arvoreVazia(TipoArvore arvore){
  return arvore==NULL;
}

TipoArvore inicializaArvore(TipoArvore arvore){
  return NULL;
}

TipoArvore destroiArvore(TipoArvore arvore){
  if(!arvoreVazia(arvore)){
    arvore->listaFilhos = destroiLista(arvore->listaFilhos);
    printf("Destruindo %c\n",arvore->dado);
    free(arvore);
  }
  return NULL;
}

TipoArvore instanciaArvore(TipoArvore arvore,char dado){
  arvore = (TipoArvore) malloc(sizeof(TipoNohArvore));
  arvore->dado = dado;
  arvore->listaFilhos = inicializaLista(arvore->listaFilhos);
  return arvore;
}

TipoArvore insereNaArvore(TipoArvore pai,TipoArvore filho){
  TipoItem item;
  item = filho;
  pai->listaFilhos = insereNoFinal(pai->listaFilhos,item);
  return pai;
}

void imprimeArvore(TipoArvore arvore,int n){
  int i;
  if(!arvoreVazia(arvore)){
    for(i=0;i<n;i++){
      printf(" ");
    }
    printf("%c\n",arvore->dado);
    imprimeLista(arvore->listaFilhos,n+1);
  }
}

void imprimeParAninhado(TipoArvore arvore, int n, int m) {
  int i = 0;
  if(!arvoreVazia(arvore)) {
    if (n != 0 && m == 0)
      printf("(");
    printf("%c", arvore->dado);
    imprimeListaAninhado(arvore->listaFilhos,n+1, 0);
    m = 1;
  }
}