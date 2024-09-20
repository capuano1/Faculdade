#include <stdio.h>
#include <string.h>

struct aluno{
  char nome[30];
  int RA;
  float notas[3];
  int frequencia;
};

void imprimeMenu();
void insereAluno(struct aluno[],int);
void listaAlunos(struct aluno[],int);
int buscaAluno(struct aluno[],int,int);
void removeAluno(struct aluno[], int, int);

int main(){
  struct aluno turmaLP[50];
  int n = 0, opcao = 0;
  int RA;
  
  while(opcao != 5){
    imprimeMenu();
    scanf("%i",&opcao);
    getchar();
    switch(opcao){
      case 1:
        if(n>0)
          listaAlunos(turmaLP,n);
        else
          printf("\nTurma vazia.\n");
        break;
      case 2:
        if(n<50){
          insereAluno(turmaLP,n);
          n++;
        }
        else
          printf("\nTurma completa. Não é possível inserir um aluno.\n");
        break;
      case 3:
        printf("RA: ");
        scanf("%i",&RA);
        if(!buscaAluno(turmaLP,n,RA))
          printf("\nAluno não encontrado.\n");
        else
          removeAluno(turmaLP, n, RA);
        n--;
        break;
      case 4:
        printf("RA: ");
        scanf("%i",&RA);
        if(!buscaAluno(turmaLP,n,RA))
          printf("\nAluno não encontrado.\n");
        break;
      case 5:
        break;
      default:
        printf("\nOpção inválida.\n");
        break;
    }
  }
}

void imprimeMenu(){
  printf("\n1 - Listar alunos");
  printf("\n2 - Inserir aluno");
  printf("\n3 - Remover aluno");
  printf("\n4 - Buscar aluno");
  printf("\n5 - Sair");
  printf("\nOpção: ");
}

void insereAluno(struct aluno turma[],int n){
  printf("\nNome: ");
  fgets(turma[n].nome,sizeof(turma[n].nome),stdin);
  turma[n].nome[strlen(turma[n].nome)-1] = '\0';
  printf("RA: ");
  scanf("%i",&turma[n].RA);
  printf("Nota 1: ");
  scanf("%f",&turma[n].notas[0]);
  printf("Nota 2: ");
  scanf("%f",&turma[n].notas[1]);
  printf("Nota 3: ");
  scanf("%f",&turma[n].notas[2]);
  printf("Frequencia: ");
  scanf("%i",&turma[n].frequencia);
  getchar();
}

void listaAlunos(struct aluno turma[],int n){
  int i;

  for(i=0;i<n;i++){
    printf("\nNome: %s",turma[i].nome);
    printf("\nRA: %i",turma[i].RA);
    printf("\nNota 1: %.2f",turma[i].notas[0]);
    printf("\nNota 2: %.2f",turma[i].notas[1]);
    printf("\nNota 3: %.2f",turma[i].notas[2]);
    printf("\nFrequencia: %i\n",turma[i].frequencia);
  }
}

int buscaAluno(struct aluno turma[],int n,int RA){
  int i;
  for(i=0;i<n;i++){
    if(turma[i].RA == RA){
      printf("\nNome: %s",turma[i].nome);
      printf("\nRA: %i",turma[i].RA);
      printf("\nNota 1: %.2f",turma[i].notas[0]);
      printf("\nNota 2: %.2f",turma[i].notas[1]);
      printf("\nNota 3: %.2f",turma[i].notas[2]);
      printf("\nFrequencia: %i\n",turma[i].frequencia);
      return 1;
    }
  }
  return 0;
}

void removeAluno (struct aluno turma[], int n, int RA) {
  int i;
  for(i=0;i<n;i++){
    if(turma[i].RA == RA) {
      strcpy(turma[i].nome, turma[n-1].nome);
      turma[i].RA = turma[n-1].RA;
      turma[i].notas[0] = turma[n-1].notas[0];
      turma[i].notas[1] = turma[n-1].notas[1];
      turma[i].notas[2] = turma[n-1].notas[2];
      turma[i].frequencia = turma[n-1].frequencia;
      break;
    }
  }
  printf("Aluno %i removido com sucesso\n", RA);
}