#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct nohArvore{
  int dado;
  struct nohArvore *subArvEsq;
  struct nohArvore *subArvDir;
};

/* Eu tentei fazer o código sem usar static, tentando mandar a varíavel sempre que eu
chamasse a função, mas não estava dando certo, eu precisava de uma variável que
continuasse com o valor sempre. Eu havia primeiro colocado dentro da função de
montar árvore, mas aí eu não conseguia zerar novamente a variável a cada caso. Então
coloquei como variável global e sempre zero ela em cada iteração de caso na função
main.
*/
static int preInd = 0;

typedef struct nohArvore TipoNohArvore;

typedef TipoNohArvore *TipoArvore;

int arvoreVazia(TipoArvore);
TipoArvore instanciaArvore(int);
TipoArvore inicializaArvore();
TipoArvore destroiArvore(TipoArvore);
TipoArvore insereNaArvoreEsq(TipoArvore,int);
TipoArvore insereNaArvoreDir(TipoArvore,int);
TipoArvore insereNaArvore(TipoArvore,int);
TipoArvore localizaMaior (TipoArvore);
TipoArvore retiraDaArvore(TipoArvore,int);
TipoArvore buscaNaArvore(TipoArvore,int);
void buscaNaArvoreExist(TipoArvore,int);
int buscaNaArvoreExistSilent(TipoArvore, int);
void imprimeArvorePreOrdem(TipoArvore);
void imprimeArvoreEmOrdem(TipoArvore);
void imprimeArvorePosOrdem(TipoArvore);

int arvoreVazia(TipoArvore arvore){
  return arvore==NULL;
}

TipoArvore instanciaArvore(int dado){
  TipoArvore arvore;
  arvore = (TipoArvore) malloc(sizeof(TipoNohArvore));
  arvore->dado = dado;
  arvore->subArvEsq = NULL;
  arvore->subArvDir = NULL;
  return arvore;
}

TipoArvore inicializaArvore(){
  return NULL;
}

TipoArvore destroiArvore(TipoArvore arvore){
  if(!arvoreVazia(arvore)){
    destroiArvore(arvore->subArvEsq);
    destroiArvore(arvore->subArvDir);
    free(arvore);
  }
  return NULL;
}

TipoArvore insereNaArvoreEsq(TipoArvore arvore,int dado){
  arvore->subArvEsq = instanciaArvore(dado);
  return arvore;
}

TipoArvore insereNaArvoreDir(TipoArvore arvore, int dado) {
  arvore->subArvDir = instanciaArvore(dado);
  return arvore;
}

TipoArvore insereNaArvore(TipoArvore arvore,int dado){
  if(!arvoreVazia(arvore)){
    if(arvore->dado>dado){
      arvore->subArvEsq = insereNaArvore(arvore->subArvEsq,dado);
    }
    else{
      if(arvore->dado<dado){
        arvore->subArvDir = insereNaArvore(arvore->subArvDir,dado);
      }
    }
  }
  else{
    arvore = instanciaArvore(dado);
  }
  return arvore;
}

TipoArvore localizaMaior (TipoArvore arvore) {
  if (arvoreVazia(arvore))
    return NULL;
  else if (arvoreVazia(arvore->subArvDir))
    return arvore;
  else
    return localizaMaior(arvore->subArvDir);
}

TipoArvore retiraDaArvore(TipoArvore arvore,int dado) {
  TipoArvore raizAux;
  if (arvoreVazia(arvore))
    return NULL;
  else if (arvore->dado > dado)
    arvore->subArvEsq = retiraDaArvore(arvore->subArvEsq, dado);
  else if (arvore->dado < dado)
    arvore->subArvDir = retiraDaArvore(arvore->subArvDir, dado);
  else if (arvore->dado == dado && !arvoreVazia(arvore->subArvDir) && !arvoreVazia(arvore->subArvEsq)) {
    raizAux = localizaMaior(arvore->subArvEsq);
    arvore->dado = raizAux->dado;
    arvore->subArvEsq = retiraDaArvore(arvore->subArvEsq, arvore->dado);
  }
  else {
    raizAux = arvore;
    if (arvoreVazia(arvore->subArvEsq))
      arvore = arvore->subArvDir;
    else if (arvoreVazia(arvore->subArvDir))
      arvore = arvore->subArvEsq;
    free(raizAux);
  }
  return arvore;
}

TipoArvore buscaNaArvore(TipoArvore arvore,int dado){
  if(arvoreVazia(arvore))
    return NULL;
  else if (arvore->dado == dado)
    return arvore;
  else if (dado < arvore->dado) {
    if (arvoreVazia(arvore->subArvEsq))
      return arvore;
    else
      return buscaNaArvore(arvore->subArvEsq, dado);
  }
  else {
    if (arvoreVazia(arvore->subArvDir))
      return arvore;
    else
      return buscaNaArvore(arvore->subArvDir, dado);
  }
}

void buscaNaArvoreExist(TipoArvore arvore, int dado) {
  if (!arvoreVazia(arvore)) {
    if (arvore->dado>dado) {
      if (arvore->subArvEsq != NULL)
        buscaNaArvoreExist(arvore->subArvEsq, dado);
      else
        printf("%i nao existe\n", dado);
    }
    else if (arvore->dado<dado) {
      if (arvore->subArvDir != NULL)
        buscaNaArvoreExist(arvore->subArvDir, dado);
      else
        printf("%i nao existe\n", dado);
    }
    else
      printf("%i existe\n", dado);
  }
  else
    printf("%i nao existe\n", dado);
}

int buscaNaArvoreExistSilent(TipoArvore arvore, int dado) {
  if (!arvoreVazia(arvore)) {
    if (arvore->dado>dado) {
      if (arvore->subArvEsq != NULL)
        buscaNaArvoreExistSilent(arvore->subArvEsq, dado);
      else
        return 0;
    }
    else if (arvore->dado<dado) {
      if (arvore->subArvDir != NULL)
        buscaNaArvoreExistSilent(arvore->subArvDir, dado);
      else
        return 0;
    }
    else
      return 1;
  }
  else
    return 0;
}

void imprimeArvorePreOrdem(TipoArvore arvore){
  if(!arvoreVazia(arvore)){
    printf(" %i",arvore->dado);
    imprimeArvorePreOrdem(arvore->subArvEsq);
    imprimeArvorePreOrdem(arvore->subArvDir);
  }  
}

void imprimeArvoreEmOrdem(TipoArvore arvore){
  if(!arvoreVazia(arvore)){
    imprimeArvoreEmOrdem(arvore->subArvEsq);
    printf(" %i",arvore->dado);
    imprimeArvoreEmOrdem(arvore->subArvDir);
  }  
}

void imprimeArvorePosOrdem(TipoArvore arvore){
  if(!arvoreVazia(arvore)){
    imprimeArvorePosOrdem(arvore->subArvEsq);
    imprimeArvorePosOrdem(arvore->subArvDir);
    printf(" %i",arvore->dado);
  }  
}

int main(){
  TipoArvore arvore, aux, parent, ord[1000];
  int cases, i, nums, arg, atual, aux1, aux2;

  scanf("%d", &cases);
  for(atual = 1; atual <= cases; atual++) {
    arvore = inicializaArvore();
    parent = inicializaArvore();
    for (i = 0; i < 1000; i++)
      ord[i] = inicializaArvore();

    scanf("%d", &nums);
    for (i = 0; i < nums; i++) {
      scanf("%d", &arg);
      aux = insereNaArvore(aux, arg);
      parent = buscaNaArvore(arvore, arg);
      if (parent == NULL)
        arvore = aux;
      else if (parent->dado > arg)
        parent->subArvEsq = aux;
      else if (parent->dado < arg)
        parent->subArvDir = aux;
    }
    printf("Case %d:\n", atual);
    aux = arvore;
    aux1 = 1;
    aux2 = 1;
    ord[0] = aux;
    while (aux != NULL) {
      printf("%d", aux->dado);
      if (!arvoreVazia(aux->subArvEsq)) {
        ord[aux1] = aux->subArvEsq;
        aux1++;
      }
      if (!arvoreVazia(aux->subArvDir)) {
        ord[aux1] = aux->subArvDir;
        aux1++;
      }
      if (ord[aux2] != NULL)
        printf(" ");
      aux = ord[aux2];
      aux2++;
    }
    printf("\n\n");
  }
  return 0;
}