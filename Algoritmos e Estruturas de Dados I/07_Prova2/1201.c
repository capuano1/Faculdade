#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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
void menu (TipoArvore);

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
  if(!arvoreVazia(arvore)){
    if(arvore->dado>dado){
      return buscaNaArvore(arvore->subArvEsq,dado);
    }
    else{
      if(arvore->dado<dado){
        return buscaNaArvore(arvore->subArvDir,dado);
      }
      else
        return arvore;
    }
  }
  return NULL;
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

void menu (TipoArvore arvore) {
  char comm[10] = "Teste";
  int arg;
  while(!feof(stdin)) {
    scanf("%s", comm);
    if (strcmp(comm, "I") == 0) {
      scanf(" %i", &arg);
      arvore = insereNaArvore(arvore, arg);
    }
    else if (strcmp(comm, "P") == 0) {
      scanf(" %i", &arg);
      buscaNaArvoreExist(arvore, arg);
    }
    else if (strcmp(comm, "R") == 0) {
      scanf(" %i", &arg);
      arvore = retiraDaArvore(arvore, arg);
    }
    else if (strcmp(comm, "PREFIXA") == 0) {
      imprimeArvorePreOrdem(arvore);
      printf("\n");
    }
    else if (strcmp(comm, "INFIXA") == 0) {
      imprimeArvoreEmOrdem(arvore);
      printf("\n");
    }
    else if (strcmp(comm, "POSFIXA") == 0) {
      imprimeArvorePosOrdem(arvore);
      printf("\n");
    }
    menu(arvore);
  }
}

int main(){
  TipoArvore arvore;
  arvore = inicializaArvore();
  menu(arvore);
}