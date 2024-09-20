#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct data{
  int dia;
  int mes;
  int ano;
};

struct aluno{
  char nome[30];
  struct data dataNasc;
  int ra;
  float notas[3];
  int freq;
};

void imprimeMenu();
void insereAluno(struct aluno[],int);
void listaAlunos(struct aluno[],int);
void removeAluno(struct aluno[], int, int);
int buscaAluno(struct aluno[],int,int);

int main(){
  struct aluno turmaAED[50];
  int n = 0, op = 0, RA;

  while(op != 5){
    imprimeMenu();
    printf("\nOpcao: ");
    scanf("%i",&op);
    switch(op){
      case 1:
        insereAluno(turmaAED,n);
        n++;
        break;
      case 2:
        printf("RA: ");
        scanf("%i",&RA);
        if(!buscaAluno(turmaAED,n,RA))
          printf("\nAluno não encontrado.\n");
        else
          removeAluno(turmaAED, n, RA);
        n--;
        break;
      case 3:
        listaAlunos(turmaAED,n);
        break;
      case 4:
        printf("RA: ");
        scanf("%i",&RA);
        if(!buscaAluno(turmaAED,n,RA))
          printf("\nAluno não encontrado.\n");
        break;
      case 5:
        printf("\nObrigado.");
        break;
      default:
        printf("\nOpção Inválida.");
        break;
    }
  }

  return 0;
}

void imprimeMenu(){
  printf("\n1 - Inserir Aluno.");
  printf("\n2 - Remover Aluno.");
  printf("\n3 - Listar Alunos.");
  printf("\n4 - Buscar Aluno.");
  printf("\n5 - Sair.");
}

void insereAluno(struct aluno turma[],int n){
  int i;

  getchar();
  printf("Nome: ");
  fgets(turma[n].nome,sizeof(turma[n].nome),stdin);
  turma[n].nome[strlen(turma[n].nome)-1] = '\0';
  printf("Data de Nascimento\n");
  printf("Dia: ");
  scanf("%i",&turma[n].dataNasc.dia);
  printf("Mes: ");
  scanf("%i",&turma[n].dataNasc.mes);
  printf("Ano: ");
  scanf("%i",&turma[n].dataNasc.ano);
  printf("RA: ");
  scanf("%i",&turma[n].ra);
  for(i=0;i<3;i++){
    printf("Nota %i: ",i+1);
    scanf("%f",&turma[n].notas[i]);
  }
  printf("Frequencia: ");
  scanf("%i",&turma[n].freq);
}

void listaAlunos(struct aluno turma[],int n){
  int i,j;

  for(i=0;i<n;i++){
    printf("\n\nNome: %s\n",turma[i].nome);
    printf("Data de Nascimento: %i/%i/%i\n",turma[i].dataNasc.dia,turma[i].dataNasc.mes,turma[i].dataNasc.ano);
    printf("RA: %i\n",turma[i].ra);
    for(j=0;j<3;j++)
      printf("Nota %i: %.2f\n",i+1,turma[i].notas[j]);
    printf("Frequencia: %i\n",turma[i].freq);
  }
}

void removeAluno (struct aluno turma[], int n, int RA) {
  int i;
  for(i=0;i<n;i++){
    if(turma[i].ra == RA) {
      strcpy(turma[i].nome, turma[n-1].nome);
      turma[i].ra = turma[n-1].ra;
      turma[i].dataNasc.dia = turma[n-1].dataNasc.dia;
      turma[i].dataNasc.mes = turma[n-1].dataNasc.mes;
      turma[i].dataNasc.ano = turma[n-1].dataNasc.ano;
      turma[i].notas[0] = turma[n-1].notas[0];
      turma[i].notas[1] = turma[n-1].notas[1];
      turma[i].notas[2] = turma[n-1].notas[2];
      turma[i].freq = turma[n-1].freq;
      break;
    }
  }
  printf("Aluno %i removido com sucesso\n", RA);
}

int buscaAluno(struct aluno turma[],int n,int RA){
  int i;
  for(i=0;i<n;i++){
    if(turma[i].ra == RA){
      printf("\nNome: %s",turma[i].nome);
      printf("\nRA: %i",turma[i].ra);
      printf("\nData de Nascimento: %i/%i/%i", turma[i].dataNasc.dia, turma[i].dataNasc.mes, turma[i].dataNasc.ano);
      printf("\nNota 1: %.2f",turma[i].notas[0]);
      printf("\nNota 2: %.2f",turma[i].notas[1]);
      printf("\nNota 3: %.2f",turma[i].notas[2]);
      printf("\nFrequencia: %i\n",turma[i].freq);
      return 1;
    }
  }
  return 0;
}