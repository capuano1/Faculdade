#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct nohArvore{
  char dado;
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
TipoArvore instanciaArvore(char);
TipoArvore inicializaArvore();
TipoArvore destroiArvore(TipoArvore);
TipoArvore insereNaArvoreEsq(TipoArvore,char);
TipoArvore insereNaArvoreDir(TipoArvore,char);
TipoArvore retiraDaArvore(TipoArvore,char);
TipoArvore buscaNaArvore(TipoArvore,char);
int buscaIndexArray(char[], int, int, char);
void imprimeArvorePreOrdem(TipoArvore);
void imprimeArvoreEmOrdem(TipoArvore);
void imprimeArvorePosOrdem(TipoArvore);
TipoArvore montaArvorePreEm(char[], char[], int, int);

int arvoreVazia(TipoArvore arvore){
  return arvore==NULL;
}

TipoArvore instanciaArvore(char dado){
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

TipoArvore insereNaArvoreEsq(TipoArvore arvore,char dado){
  arvore->subArvEsq = instanciaArvore(dado);
  return arvore;
}

TipoArvore insereNaArvoreDir(TipoArvore arvore, char dado) {
  arvore->subArvDir = instanciaArvore(dado);
  return arvore;
}

TipoArvore retiraDaArvore(TipoArvore arvore,char dado) {
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

TipoArvore buscaNaArvore(TipoArvore arvore,char dado){
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

/* À princípio, eu fazia essa busca de index em uma função só, a função de montar arvore
à partir da Pré-Ordem e Em-Ordem, mas como ela ficou repetida 2x naquela função, além de
fazer com que eu criasse mais variáveis, decidi só deixar uma função separada específica
para fazer isso. Essa função irá localizar qual o índice dentro da "lista" de caracteres
dada, assim localizando os dados em relação às raízes nas ordens dadas. Crucial para se
montar a árvore neste dado exercício.
*/

int buscaIndexArray(char array[], int inicio, int fim, char dado) {
  int i;
  for (i = inicio; i <= fim; i++) {
    if (array[i] == dado)
      return i;
  }
}

void imprimeArvorePreOrdem(TipoArvore arvore){
  if(!arvoreVazia(arvore)){
    printf("%c",arvore->dado);
    imprimeArvorePreOrdem(arvore->subArvEsq);
    imprimeArvorePreOrdem(arvore->subArvDir);
  }  
}

void imprimeArvoreEmOrdem(TipoArvore arvore){
  if(!arvoreVazia(arvore)){
    imprimeArvoreEmOrdem(arvore->subArvEsq);
    printf("%c",arvore->dado);
    imprimeArvoreEmOrdem(arvore->subArvDir);
  }  
}

void imprimeArvorePosOrdem(TipoArvore arvore){
  if(!arvoreVazia(arvore)){
    imprimeArvorePosOrdem(arvore->subArvEsq);
    imprimeArvorePosOrdem(arvore->subArvDir);
    printf("%c",arvore->dado);
  }  
}

/* Função recursiva central que irá receber as "listas" de caracteres Em-Ordem e Pré-Ordem
para montar a árvore. Após a montagem da árvore, usarei a função já implementada para aqui
para imprimir a árvore em Pós-Ordem.
*/

TipoArvore montaArvorePreEm(char pre[52], char em[52], int emIni, int emFim) {
  //Caso seja inválida
  if (emIni > emFim)
    return NULL;
  TipoArvore arvore = instanciaArvore(pre[preInd++]);
  //Caso seja árvore com apenas 1 raíz, apenas 1 dado, o trabalho já foi feito:
  if (emIni == emFim)
    return arvore;
  /*Se não acabou, vamos agora quebrar o trabalho em duas partes: direita e esquerda. Para
  isso, vamos achar onde está a raiz principal, já que tudo à esquerda dela Em-Ordem está na
  subárvore esquerda, e tudo à direita está na subárvore direita.
  */
  int indEmOrd = buscaIndexArray(em, emIni, emFim, arvore->dado);
  arvore->subArvEsq = montaArvorePreEm(pre, em, emIni, indEmOrd - 1);
  arvore->subArvDir = montaArvorePreEm(pre, em, indEmOrd + 1, emFim);
  return arvore;
}

int main(){
  int cases, i, nums;
  scanf("%d", &cases);
  for (i = 1; i <= cases; i++) {
    preInd = 0;
    TipoArvore arvore;
    arvore = inicializaArvore();
    char pre[52], em[52];
    scanf("%d %s %s", &nums, pre, em);
    arvore = montaArvorePreEm(pre, em, 0, nums - 1);
    imprimeArvorePosOrdem(arvore);
    printf("\n");
    destroiArvore(arvore);
  }
}