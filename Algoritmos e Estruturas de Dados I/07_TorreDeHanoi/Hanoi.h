#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXDISK 10
#define MAXPLAY 2000

typedef struct {
  int tamanho;
} Tipodisco;

struct noh {
  Tipodisco disco;
  struct noh *prox;
};

typedef struct noh TipoNoh;

typedef struct {
  TipoNoh *topo;
} TipoPilha;

void inicializaPilhaHanoi (TipoPilha *, TipoPilha *, TipoPilha *);
void destroiPilha (TipoPilha *);
int pilhaVazia (TipoPilha *);
int inicializaHanoi (TipoPilha*, int );
int trocaPos (int, int, TipoPilha *, TipoPilha *, TipoPilha *);
int checaHanoi (int, int, TipoPilha *, TipoPilha *, TipoPilha *);
int checaVitoria (TipoPilha *, int);