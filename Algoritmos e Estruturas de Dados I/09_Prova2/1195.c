#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct nohArvore{
  int dado;
  struct nohArvore *subArvEsq;
  struct nohArvore *subArvDir;
};

typedef struct nohArvore TipoNohArvore;

typedef TipoNohArvore *TipoArvore;

int arvoreVazia(TipoArvore);
TipoArvore instanciaArvore(int);
TipoArvore inicializaArvore();
TipoArvore destroiArvore(TipoArvore);
TipoArvore insereNaArvore(TipoArvore,int);
TipoArvore retiraDaArvore(TipoArvore,int);
TipoArvore buscaNaArvore(TipoArvore,int);
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

TipoArvore retiraDaArvore(TipoArvore arvore,int dado) {
    if (!arvoreVazia(arvore)) {
        if (arvore->dado == dado)
            destroiArvore(arvore);
        else if (arvore->dado > dado)
            retiraDaArvore(arvore->subArvEsq, dado);
        else
            retiraDaArvore(arvore->subArvEsq, dado);
    }
    else {
        return NULL;
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

void imprimeArvorePreOrdem(TipoArvore arvore){
  if(!arvoreVazia(arvore)){
    printf(" %d",arvore->dado);
    imprimeArvorePreOrdem(arvore->subArvEsq);
    imprimeArvorePreOrdem(arvore->subArvDir);
  }  
}

void imprimeArvoreEmOrdem(TipoArvore arvore){
  if(!arvoreVazia(arvore)){
    imprimeArvoreEmOrdem(arvore->subArvEsq);
    printf(" %d",arvore->dado);
    imprimeArvoreEmOrdem(arvore->subArvDir);
  }  
}

void imprimeArvorePosOrdem(TipoArvore arvore){
  if(!arvoreVazia(arvore)){
    imprimeArvorePosOrdem(arvore->subArvEsq);
    imprimeArvorePosOrdem(arvore->subArvDir);
    printf(" %d",arvore->dado);
  }  
}

int main(void){
  int nums, cases, dado, i1, i2;
  int *v;
  scanf("%d", &cases);
  for (i1 = 1; i1 <= cases; i1++) {
    TipoArvore arvore = inicializaArvore();
    scanf("%d", &nums);
    v = malloc(nums * sizeof(int));
    for (i2 = 0; i2 < nums; i2++) {
      scanf("%d", &v[i2]);
      arvore = insereNaArvore(arvore, v[i2]);
    }
    printf("Case %i:", i1);
    printf("\nPre.:");
    imprimeArvorePreOrdem(arvore);
    printf("\nIn..:");
    imprimeArvoreEmOrdem(arvore);
    printf("\nPost:");
    imprimeArvorePosOrdem(arvore);
    printf("\n\n");
    destroiArvore(arvore);
    getchar();
    free(v);
  }
  return 0;
}