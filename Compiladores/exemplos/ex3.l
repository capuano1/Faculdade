%option noyywrap
%{
    #include<stdio.h>
    #include<stdlib.h>
    #include<string.h>

    int contVogal     = 0,
        contConsoante = 0;

    // Leis de métodos...
%}

VOGAIS (a|e|i|o|u|A|E|I|O|U)
CONSOANTES [A-Za-z]

%%

{VOGAIS} {
    contVogal++;
}

{CONSOANTES} {
    contConsoante++;
}

. {
    // Faça nada...
}

\n {
// Faça nada...
}
%%

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

    printf("Vogais:%d\nConsoantes:%d",contVogal,contConsoante);


    return 1;
}