%option noyywrap
%{
    int uppers = 0;
%}

%%
[A-Z][a-zA-Z]*      {uppers++;}
[\n]                {}
.                   {}
%%

#include <stdio.h>

extern FILE *yyin;
extern int uppers;

int main(void) {
    yyin = fopen("texto.txt", "r");
    if (!yyin) {
        perror("texto.txt");
        return 1;
    }

    yylex();

    fclose(yyin);

    printf("%d palavras maiusculas\n", uppers);
    return 0;
}


/*int main(int argc, char **argv) {
    if (argc > 1) {
        if (!(yyin = fopen(argv[1], "r"))) {
            perror(argv[1]);
            return 1;
        }
    }

    yylex();

    printf("%d palavras maiusculas\n", uppers);

    return 0;
}
*/