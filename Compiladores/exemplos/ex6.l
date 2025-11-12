%option noyywrap
%{
    #include<stdio.h>
    #include<stdlib.h>
    #include<string.h>

    //typedef enum {INTEIRO, FLUTUANTE} Numero;
    
    typedef struct {
        char  tipo[50];
        char  valor[50];
    } Lexema;

    Lexema *lexemas;
    int quantidade_lexemas = 0;

    // Leis de métodos...
    void install_num(char* texto);
%}

DIGITOS [0-9]

%%

(R\$)[ ]*{DIGITOS}+,{DIGITOS}{DIGITOS} {
    // Número flutuante/pseudoreal
    install_num(yytext);
}


(.|\n) {
    // Faça nada...
}
%%

void install_num(char* texto){
    lexemas = realloc(lexemas, (quantidade_lexemas + 1) * sizeof(Lexema));

    strcpy(lexemas[quantidade_lexemas].tipo,"MONEY");
    strcpy(lexemas[quantidade_lexemas++].valor, texto); 
}

extern FILE *yyin;
int main(int argc, char** argv){
    
    if(argc > 1){
        if ((yyin = fopen(argv[1], "r")) <= 0){
            perror("Não deu pra ler");

            return -1;
        }
    }
    else{
        if ((yyin = fopen("exemplo2.txt", "r")) <= 0){
                perror("Não deu pra ler");

                return -1;
            }
    }

    yylex();

    fclose(yyin);

    int i = 0;
    for(; i < quantidade_lexemas; i++)
        printf("<%s,%s>\n",lexemas[i].tipo,lexemas[i].valor);


    return 1;
}