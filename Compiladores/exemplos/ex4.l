%option noyywrap
%{
    #include<stdio.h>
    #include<stdlib.h>
    #include<string.h>

    int contChars = 0,
        contWords = 0,
        contLines = 1;

    // Leis de métodos...
%}

LETRAS [A-Za-z]

%%

{LETRAS}+ {
    contWords++;
    contChars += strlen(yytext);
}

. {
    // Faça nada...
    contChars++;
}

\n {
// Faça nada...
    contChars++;
    contLines++;
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

    printf("Palavras:%d\nChars:%d\nLinhas:%d",contWords,
    contChars,contLines);


    return 1;
}