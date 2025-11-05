%option noyywrap
%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int countPalavras = 0;
%}

MAIUSCULAS [A-Z]
MINUSCULAS [a-z]

%%

{MAIUSCULAS}{MINUSCULAS}+ {
    countPalavras++;
}

. {

}

\n {

}
%%

extern FILE *yyin;
int main (int argc, char** argv) {
    if (argc > 1) {
        if ((yyin = fopen(argv[1], "r")) <= 0) {
            perror("Impossivel ler");
            return -1;
        }
    }
    else {
        if ((yyin = fopen("exemplo.txt", "r")) <= 0) {
            perror("Impossivel ler");
            return -1;
        }
    }

    yylex();
    fclose(yyin);
    printf("Palavras: %i\n", countPalavras);

    return 1;
}