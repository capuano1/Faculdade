#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define GREEN "\e[0;32m"
#define WHITE "\e[0;37m"
#define BLUE  "\e[0;34m"

#define FALSE 0
#define TRUE 1

void printDir(){
  system("sleep 1");
  char dir[100];
  getcwd(dir,sizeof(dir)); // tenho o diretorio
  char *user = getenv("USER"); // tenho o user
  char host[100];
  gethostname(host,sizeof(host)); // nome da maquina

  // execvp("hostname",NULL)

  char* actual = strtok(dir, "/");
  char** address = malloc(sizeof(char*) * 10);
  int i = 0, count;

  while(actual != NULL){
    if(strcmp(actual, user) == 0) // acho a posição do user em dir
      count = i; // address[count] = "runner"

    address[i] = actual;
    actual = strtok(NULL, "/");
    i++;
  }

  // user:~/
  printf(GREEN"%s@%s"WHITE":"BLUE"~/",user,host);

  if(i>4)
    //add[0] = home 

    // user:~/.../address/adress
    printf(".../%s/%s",address[i-2],address[i-1]);
  else{
    // user:~/address/address
    for(int j=count+1; j<i-1; j++)
      printf(BLUE"%s/",address[j]);
    printf(BLUE"%s",address[i-1]);
  }
  // user:~/.../address/adress$
  // user:~/address/address$
  printf(WHITE"$ ");

  // for(int j=0; j<i; j++){
  //   free(address[j]);
  // }
}

int* identificaOperador(char** argumentos){

  int* operadorEposicao = (int *) malloc(sizeof(int)*2); // ops[2] ;
  int i=0;
  while(argumentos[i] != NULL){
    if(strcmp(argumentos[i], "||")==0){ // OR
      operadorEposicao[0] = 0;
      operadorEposicao[1] = i;
      return operadorEposicao;
    }
    if(strcmp(argumentos[i], "&&")==0){ // AND
      operadorEposicao[0] = 1;
      operadorEposicao[1] = i;
      return operadorEposicao;
    }
    if(strcmp(argumentos[i], "|")==0){ // pipe
      operadorEposicao[0] = 2;
      operadorEposicao[1] = i;
      return operadorEposicao;
    }
    if(strcmp(argumentos[i], "&")==0){ // background
      operadorEposicao[0] = 3;
      operadorEposicao[1] = i;
      return operadorEposicao;
    }
    i++;
  }
  operadorEposicao[0] = -1; // não tem operador
  return operadorEposicao;
}

int fazCd(char** argumentos,int i) {
  if(i == 1){// cd
    char *home = getenv("HOME");
    chdir(home);
    return 0;
  }

  if(strcmp(argumentos[1],"..") == 0){ // retorna o diretorio
    chdir("..");
    return 0;
  }

  if(chdir(argumentos[1]) != 0){ 
    // se chdir não funcionar, da erro
    perror("cd error");
    return -1;
  }
return 0;
}

void executaPipe(char** arg, int tamanho) {
  //tamanho = quantos argumentos
  //count = quantos pipes
  //fd = File Descriptor, para o pipe
  int count = 0, fd[2], i, j = 0;
  //Solução genial que criamos para passar o comando certo para o execvp em execuções subsequentes (que precisariam rodar comandos que não estão em arg[0])
  char **comando = arg;


  //Um for que conta quantos pipes temos, e já coloca NULL no lugar do pipe, o que separa os comandos, deixando-os no jeito que o execvp precisa
  char pip[2] = "|";
  for (i = 0; i < tamanho; i++) {
    if(strcmp(arg[i], pip) == 0) {
      count++;
      arg[i] = NULL;
    }
  }

  //Essa é a variável que vai enviar o resultado do processamento anterior para o próximo. Ela começa em 0 por ser o mesmo valor de STDIN_FILENO
  int result_anterior = STDIN_FILENO;

  //Vale ressaltar aqui que count seria o número de comandos (e seus argumentos) - 1, ou seja, é o número de comandos a serem executados - 1.
  //Isso é importante pois o último comando NÃO pode ser processado de maneira iterativa, já que vamos mudar o stdout para entrar no próximo comando.
  //Ou seja, o stdout não será o terminal nestes casos resolvidos iterativamente. Mas o último comando precisa retornar no terminal. Então ele é tratado de maneira quase similar (diferença apenas do stdout).
  for (i = 0; i < count; i++) {
    if (pipe(fd) < 0) {
      printf("Broken Pipe\n");
      return;
    };

    //Aqui, vamos implementar tudo o que o filho (criado após o fork) precisa fazer. Ele precisa fazer a maioria das coisas neste caso.
    pid_t pid = fork();
    //Curiosidade: o número de processos filhos criados será o mesmo de sinais de pipe ('|') no comando
    if(pid == 0) {
      //Essa condicional só não é verdadeira na primeira iteração.
      //Nas iterações subsequentes, ela quem vai injetar o resultado do processamento anterior no novo processamento (resultado do comando anterior no novo)
      //Lembrando que como cada processo possui sua própria file descriptor table, não teremos problemas ao mexer com STDIN_FILENO ou STDOUT_FILENO
      if (result_anterior != STDIN_FILENO) {
        dup2(result_anterior, STDIN_FILENO);
        close(result_anterior);
      }
      //Provavelmente a parte mais importante dessa implementação: enviar o resultado do processamento (do execvp em seguida) para o write-end do pipe fd
      //Lembrando que ao fazer dup2, o programa realiza um close(STDOUT_FILENO)
      dup2(fd[1], STDOUT_FILENO);
      //Agora podemos fechar fd[1], pois já fizemos o redirecionamento de stdout para ele.
      close(fd[1]);

      //Agora podemos realizar execvp. Lembrando que o execvp lê os argumentos até o NULL. Com isso, garantimos que o comando antes do pipe em questão será o único sendo realizado.
      //Cabe ressaltar que como redirecionamos STDOUT (e, com isto, o fechamos), o resultado deste execvp, ao invés de ir para o terminal, irá ser escrito em fd[1], ou seja, no write-end do nosso pipe.
      execvp(comando[0], comando);
      exit(1);
    }
    //Agora, os comandos do processo pai
    //Estes são mais simples, já que o pai só precisa pegar o resultado que o filho gerou e enviar para a próxima iteração (indiretamente, para o próximo filho)
    else if (pid > 0) {
      //Preciso que o processo pai espere o processo filho terminar de processar
      waitpid(0, NULL, 0);
      //Agora, a nossa variável de resultado anterior (de processamento anterior), recebe o read-end do nosso pipe, isto é, o resultado de nosso último processamento
      //Com esta variável contendo o resultado do último processamento, na próxima iteração, ele os enviará para o novo comando ao fazer dup ligando ele e STDIN_FILENO
      close(result_anterior);
      close(fd[1]);
      result_anterior = fd[0];
      //Agora, antes de terminarmos a iteraçao, precisamos garantir que o próximo comando a ser executado será realmente o correto (isto é, executar o segundo comando, após o primeiro pipe, na segunda iteração, e por aí vai)
      //tl;dr: Vamos fazer o programa "esquecer" o comando que já foi executado
      //Primeiramente, este elegante for (elegante pois não precisou abrir chaves para resover o problema) irá encontrar onde está o próximo NULL. Com isso, fazemos j++ para estarmos no índice do começo do próximo comando (lembrando que no começo do código, alteramos todos os pipes por NULL).
      for(j = 0; comando[j] != NULL; j++);
      j++;
      //Com isso, fazemos com que o ponteiro aponte para o endereço de memória em que o próximo comando começa.
      comando = &comando[j];
    }
  }
  //Estando agora fora do loop de for, significa que n-1 comandos foram processados (isto é, apenas o último comando não foi processado)
  //Temos tudo que precisamos para processar o último comando, já que o resultado do comando n-1 (que seria o processamento dele com o resultado do comando n-2 e por aí vai) está na nossa variável result_anterior
  //Agora fora do loop, também não estaremos mexendo com o STDOUT, o que significa que este último comando será enviado para o Standart Output, que seria o nosso terminal
  //O uso desta condicional, a primeira vista, poderia ser questionado. Porém, ele é necessário para alguns casos em que o resultado anterior pode não estar carregando nada (como por exemplo em operadores booleanos e pipe, A && B | C com A sendo falso).
  if (result_anterior != STDIN_FILENO) {
    dup2(result_anterior, STDIN_FILENO);
    close(result_anterior);
  }

  //Lembrando que dentro do loop de for, nós tiramos os comandos já executados do array. Dessa forma, temos no momento o comando final e um NULL (tecnicamente temos alguns resquícios lixo dos outros comandos, mas eles são irrelevantes).
  execvp(comando[0], comando);
  exit(1);
}

// -------------------------------------------------------------------


int main() {
  pid_t pid;
  char input[300];
  // array com os argumentos do comando
  //Tive que aumentar o valor da multiplicação (era 10 antes, mas estava dando alguns problemas em comandos imensos específicos, aumentar bastante esse número resolveu)
  char** argumentos = malloc(sizeof(char*)*500), // input original
  **comando, // copia do input
  **backup;  // backup do comando

  int *ops, retornoP=0;

  printf("Iniciando Projeto 1 de Sistemas Operacionais: shell LINUX\n");

  // LOOP
  while(1){
    inicio:
    printDir();
    // adquire o input
    fgets(input, sizeof(input), stdin);
    input[strlen(input)-1] = '\0';

    int aux = 0, len = strlen(input), quot = 0;
    //O comando abaixo remove as aspas dos comandos. Para serem enviados para o execvp, eles não podem conter aspas duplas para funcionar.
    //Porém, caso o argumento possua um espaço entre as aspas, eu mudo esse caracter espaço (32) para aspas (34). Pois o nosso strtok separa tudo por espaço, então essa aspas vai tomar o lugar indicando que ali deveria ter um espaço, mas que é 1 argumento só, então não pode ser separado.
    for (int z = 0; z+aux < len; z++) {
      if (input[z+aux] == 34) {
        aux++;
        quot++;
        if (input[z+aux+1] == 34) aux++;
      }
      if (aux != 0) input[z] = input[z+aux];
      if (input[z] == 32 && quot % 2 == 1) input[z] = 34;
    }
    if (aux != 0) input[len-aux] = '\0';

    // strtok pra pegar/separar cada palavra do comando
    char *palavra = strtok(input, " ");
    int i = 0;
    while(palavra != NULL){
      argumentos[i] = palavra;
      palavra = strtok(NULL, " ");
      i++;
    }
    argumentos[i] = NULL;

    char exitstr[5] = "exit";
    //Essa checagem garante que, caso o shell não receba nada do usuário (o usuário dê apenas enter), o shell simplesmente volte para o começo ao invés de dar um Segmentation Fault
    if (argumentos[0] == NULL) goto inicio;
    else if (strcmp(argumentos[0], exitstr) == 0) return 0;
    int amp = -1;
    char ampers[2] = "&";
    //Agora, fazemos a checagem de cada argumento para procurar argumentos que possuem o caracter " (34), e substituimos pelo espaço (32), que seria o correto aqui.
    //Fora isso, eu faço a checagem para detecção do ampersand (&) (detecta se há ampersand na string e se ela tem apenas 1 ampersand (strlen), senão teríamos falso positivo em casos &&) e se achar, qual o índice dele.
    for (int x = 0; x < i; x++) {
      char *auxchar = strchr(argumentos[x], 34);
      while (auxchar != NULL) {
        auxchar[0] = 32;
        auxchar = strchr(argumentos[x], 34);
      }
      if (strchr(argumentos[x], 38) && strlen(argumentos[x]) == strlen(ampers)) 
        amp = x;
    }
    //Caso ampersand (&) exista (amp != -1), eu transformo ele em NULL para poder passar o comando no execvp sem problemas e, no caso do filho (que executará o comando em background), deixo como NULL todos os outros comandos que vêm após, enquanto no caso do pai, atualizo o ponteiro de argumentos dele para que ele saiba apenas os argumentos restantes após o &
    int pidamp;
    if (amp != -1) { // é &
      argumentos[amp] = NULL; // & -> NULL
      pidamp = fork();
      if (pidamp == 0) { //filho
        // cmd1 & cmd2
        for (int g = amp; g < i; g++) argumentos[g] = NULL;
        // cmd1 NULL NULL
      }
      else if (pidamp > 0) {//pai
        // argumentos = cmd1 & cmd2
        argumentos = &argumentos[amp+1];
        //printf("%s", argumentos[1]);
        // argumentos = cmd2
        if (argumentos[0] == NULL) goto inicio;
      }
    }
    else if (amp == -1) { // qualquer coisa
      amp = 0;
      pidamp = fork();
      if (pidamp > 0) { 
        waitpid(0, NULL, 0);
        goto inicio;
      }
    }

    char pip[2] = "|";
    int tamanho = i;
    for (int j = 0; j < tamanho - 1 - amp; j++) {
      if (strcmp(argumentos[j], pip) == 0 && strlen(argumentos[j]) == strlen(pip)) {
        if (fork() == 0) executaPipe(argumentos, tamanho - amp - 1);
        waitpid(0, NULL, 0);
        //printf de teste para ver se encontrava o pipe:
        //printf("Achei um gatinho\n");
        //goto basicamente volta até o começo do while, basicamente ele chama outra iteração. Foi necessário usar goto pois este código aqui está dentro de um for, então precisaria dar break; deste for e continue; no while de fora. Neste caso, a solução é usar goto.
        //Quebrei a cabeça pois antes estava dando core dumped pois ele continuava o código aqui da main quando não deveria, já que a string estava sendo processada pelo executaPipe(). goto resolveu isso.
        if (pidamp == 0) return 0;
        goto inicio;
      }
    }
    comando = argumentos;

    /*
      É feito um loop do-while por dois motivos:
      1- o input pode ter mais de um operador, por isso o loop
    é feito até que não tenha mais operadores.
      2- o loop precisa ser realizado ao menos uma vez, pois há
    o caso de um comando sem operador lógico, assim é executa o
    comando e sai do loop do-while, mas se mantém no loop ite-
    rivo do shell.
    */

    do{
      // identifica o operador
      ops = identificaOperador(comando); 

      /*
      ops[0] = operador
      ops[1] = posição do operador

        Após fazer identificaOperador, eu substituo o operador por 
      NULL, pois ao chamar execvp, ele executa até NULL e eu coloco
      um backup apontando para o comando após o operador substituido
      por NULL, assim quando o loop terminar, ele é executado como 
      um novo input.
        Isto caso o comando tenha operadores
      */
      if(ops[0] != -1){
        comando[ ops[1] ] = NULL;
        if (comando[ ops[1]+1 ] != NULL)
          backup = &comando[ ops[1]+1 ];
      }


      pid = fork();

      /*
        Eu tenho a lista de argumentos e um vetor que na posição 0
      me diz qual é o operador e na posição me mostra sua posição
      na lista de argumentos.
      */

      if(ops[0] == -1){ // sem operadores
        if(strcmp(comando[0],"exit") == 0){
          exit(1);
        }
        if(pid > 0) // pai
          wait(NULL); 

        else{// filho
          if(strcmp(comando[0],"cd") == 0){
            fazCd(comando, i);
          }
          else if(strcmp(comando[0],"exit") == 0){
            exit(1);
          }
          else{
            execvp(comando[0], comando); 
          }
        }

      }//ops[0]==-1 s/ operador

      if(ops[0] == 0){ // ||
      /*    comando || backup
      Se o comando é executado, retorna para o loop
      Senão, o backup é executado.
      */ 

        if(pid == 0){// filho
          execvp(comando[0], comando);
        }

        else if (pid > 0){
          // o filho executou o programa?
          // retornoP mostra se sim/não
          waitpid(-1, &retornoP, WEXITSTATUS(retornoP));
        }


        if(retornoP == 0)
          // se o comando foi executado, sai do do-while
          ops[0] = -1;
      }//ops[0]==0 ||

      if(ops[0] == 1){ //ops[0]==0 &&

        if(pid == 0){// filho
          execvp(comando[0], comando);
        }

        else if (pid > 0){
          // o filho executou o programa?
          // retornoP mostra se sim/não
          waitpid(-1, &retornoP, WEXITSTATUS(retornoP));
        }

        // se o filho falhou
        if(retornoP != 0){ 

/*  "mkdir teste1 && ls || cd teste1"
    "mkdir teste1 && ls" falhou, mas cd teste1 ainda pode ser executado*/

          //comando1 falhou, mas comando2 pode ser executado
          comando = backup;
          do{
            ops = identificaOperador(comando);
            // não tem mais operadores, dá break e
            // e continua no do-while original
            if(ops[0]==-1)
              break;
            backup = &comando[ ops[1]+1 ];

          // enquanto não for ||
          }while(ops[0] != 0); 
          // se tiver, executar o comando após ||
          // ls || cd teste1
          if(ops[0] != -1){
          //se esse comando não for único
            comando = backup;
            // cd teste1
          }

        }

      }//ops[0]==1 &&

      
      if(backup != NULL)
        comando = backup;
    }while(ops[0]!=-1);

  if (pidamp == 0) return 0;
  }//while(1)

}//main



// mkdir dir || cd teste1
// sleep 5 && echo hello &