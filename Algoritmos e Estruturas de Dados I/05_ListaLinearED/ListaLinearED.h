#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
  int chave;
  char nome[30];
} TipoItem;

struct noh{
  TipoItem item;
  struct noh *prox;
};

typedef struct noh TipoNoh;

typedef struct{
  TipoNoh *inicioLista;
  int ultimo;
} ListaLinearED;

int listaVaziaLLED(ListaLinearED*);
void inicializaListaLLED(ListaLinearED*);
void destroiListaLLED(ListaLinearED*);
void imprimeItemLLED(TipoItem);
void imprimeListaLLED(ListaLinearED*);
int insereNoFinalLLED(ListaLinearED*,TipoItem);
int insereNaPosicao(ListaLinearED *, TipoItem, int);
int insereNoInicioLLED(ListaLinearED*,TipoItem);
int removeDoFinalLLED(ListaLinearED*,TipoItem*);
int removeEspecifico (ListaLinearED *, TipoItem *, int);
int removeDaPosicao(ListaLinearED *, TipoItem *, int);
int removeDoInicioLLED(ListaLinearED*,TipoItem*);