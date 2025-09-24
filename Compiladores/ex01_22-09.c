#include <stdio.h>
#include <string.h>

// Estados do autômato
typedef enum {Q0, Q1, Q2, QLixo} Estado;
typedef struct {
    char tipo[50];
    char valor[50];
} Lexema;
// booleano

// Função para verificar se um dado caracter c é
// um caracter alfabético: [a-zA-Z]
int eh_letra(char c) {
    if (((c >= 'a') && (c <= 'z')) || ((c >= 'A') && (c <= 'Z'))) {
        return 1;
    }
    return 0;
}

// Função para verificar se um dado caracter c é
// um caracter numérico: [0-9]
int eh_digito(char c) {
    if ((c >= '0') && (c <= '9')) {
        return 1;
    }
    return 0;
}

// Programação do autômato
// [a-zA-Z]([a-zA-Z0-9]*)
int AFD(char *cadeia, int verbose, int i) {
    
    char traco[1000] = "";
         //lexema[1000] = "";
    Lexema lexema;

    Estado q = Q0; // Start
    if (verbose) {
        strcat(traco, "Q0");
    }

    char c = cadeia[i];
    //int i;

    if (!eh_letra(c)) {
        q = QLixo;
        i++;
        if (verbose) {
            strcat(traco, "->QLixo");
        }
    }
    else {
        int i_lexema = 0;
        lexema.valor[i_lexema] = c;
        i_lexema++;
        q = Q1;
        if (verbose) {
            strcat(traco, "->Q1");
        }
        i++;
        for (/*i = 1*/; q != Q2; i++) {
            c = cadeia[i]; // i-ésimo caracter
            if(eh_letra(c) || eh_digito(c)) {
                q = Q1;
                if (verbose) {
                    strcat(traco, "->Q1");
                }
                lexema.valor[i_lexema] = c;
                i_lexema++;
            } else {
                q = Q2;
                if (verbose) {
                    strcat(traco, "->Q2");
                }
                // break;
            }
        }
        lexema.valor[i_lexema] = '\0';
        /*
        if ((q == Q1) && (cadeia[i] == '\0')) {
            q = Q2;
            if (verbose) {
                strcat(traco, "->Q2");
            }
        }
        else {
            q = QLixo;
            if (verbose) {
                strcat(traco, "->QLixo");
            }
        }
        */
    }

    if (verbose) {
        printf("Traco: %s\n", traco);
        printf("Lexema: %s\n", lexema);
    }
    /*
    if (q == Q2) return 1;
    else return 0;
    */
    return i;
}

void varredura(char *cadeia) {
    
    for (int i = 0; cadeia[i] != '\0';) { 
        i = AFD(cadeia, 1, i);
    }

}

int main () {
    char teste[100] = "mouse+teclado+monitor+=CPU123";

    varredura(teste);

    //int aceita = AFD(teste, 1, 0);

    /*
    if (aceita) printf("A string %s eh aceita pelo AFD!", teste);
    else printf("A string %s nao eh aceita pelo AFD!", teste);
    */
}