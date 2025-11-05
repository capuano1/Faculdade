%option noyywrap
%{
    #include<stdio.h>
    #include<stdlib.h>
    #include<string.h>

    int contVogal     = 0,
        contConsoante = 0;

    // Leis de métodos...
%}



%%


. {
    // Faça nada...
}
%%

extern FILE *yyin;
int main(void){
    // yyin: ponteiro de arquivo para o flex/lex

    //yyin = fopen("exemplo.txt", "r");
if ((yyin = fopen("exemplo.txt", "r")) <= 0){
        perror("Não deu pra ler");

        return -1;
    }
    else{
        yylex();

        fclose(yyin);

        printf("Maiusculas:%d\nMinusculas:%d\nDigitos:%d",contMaiuscula,contMinuscula,contDigito);
    }

    return 1;
}