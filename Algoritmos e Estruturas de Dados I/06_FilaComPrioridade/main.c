#include "GeradorSenhas.h"

void imprimeMenu();
void leDadosItem(TipoItem*);

int filaNormal = 301, filaPrior = 1;

int main(){
  TipoFila fila;
  TipoItem item;
  int op = 0, i;

  inicializaFila(&fila);

  while(op != 4){
    imprimeMenu();
    printf("\nOpção: ");
    scanf("%i",&op);
    switch(op){
      case 1:
        leDadosItem(&item);
        if(insereNaFila(&fila,item))
          printf("\nSucesso!\n");
        else
          printf("\nErro! Não foi possível inserir o item!\n");
        break;
      case 2:
        if(retiraDaFila(&fila,&item)){
          printf("\nChamando próximo da fila:");
          printf("\nSenha: %i \nCliente: %s\n",item.senha,item.nome);
        }
        else{
          printf("\nErro! Não foi possível chamar o próximo da fila!\n");
        }
        break;
      case 3:
        if(!filaVazia(&fila)){
          printf("\nFila:\n");
          imprimeFila(&fila);
        }
        else{
          printf("\nFila Vazia!\n");
        }
        break;
      case 4:
        destroiFila(&fila);
        printf("\nAté logo!\n");
        break;
      default:
        break;
    }
  }

  return 0;
}

void imprimeMenu(){
  printf("\nBem-Vindo! Selecione uma opção");
  printf("\n1 - Retirar senha");
  printf("\n2 - Chamar próximo");
  printf("\n3 - Imprimir fila");
  printf("\n4 - Sair");
}

void leDadosItem(TipoItem *item){
  int aux = 5, senha = 0;
  do {
    printf("\nPrioritário? Digite 1, senão, digite 0: ");
    scanf("%i",&aux);
  }
  while (aux != 0 && aux != 1);  
  item->prioridade = aux;
  getchar();
  if (aux == 0) {
    senha = filaNormal;
    filaNormal++;
  }
  else {
    senha = filaPrior;
    filaPrior++;
  }
  item->senha = senha;
  printf("Nome: ");
  fgets(item->nome,sizeof(item->nome),stdin);
  item->nome[strlen(item->nome)-1] = '\0';
  printf("Sua senha é %i", senha);
}