#include <stdio.h> // stdio.h
#include <string.h> // string.h

// Estados do AFD
typedef enum { Q0, Q1, Q2, QLixo } Estado;

typedef struct {
	char tipo[50];
	char valor[50];
} Lexema;

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
int AFD_ID(char* cadeia, int verbose, int i, Lexema *lexema, int *k) {

	char traco[1000] = "";
		//lexema[1000] = "";

	//Lexema lexema;


	Estado q = Q0; // Start
	if (verbose) {
		strcat(traco, "Q0");
	}

	char c = cadeia[i];
	//int i;

	if (!eh_letra(c)) {
		q = QLixo;
		if (verbose) {
			strcat(traco, "->QLixo");
		}
	}
	else {

		strcpy(lexema->tipo, "ID");

		int i_lexema = 0;

		lexema->valor[i_lexema] = c;
		i_lexema = i_lexema + 1;

		q = Q1;
		if (verbose) {
			strcat(traco, "->Q1");
		}
		i = i + 1;
		for (/*i = 1*/; q != Q2; i++) {
			c = cadeia[i]; // i-ésimo caractere

			if (eh_letra(c) || eh_digito(c)) {
				q = Q1;
				if (verbose) {
					strcat(traco, "->Q1");
				}
				lexema->valor[i_lexema] = c;
				i_lexema = i_lexema + 1;

			}
			else {
				q = Q2;
				if (verbose) {
					strcat(traco, "->Q2");
				}
				i = i - 1;
				//break;
			}
		}
		lexema->valor[i_lexema] = '\0';
		*k = *k + 1;
	}

	if (verbose) {
		printf("\nTraco: %s\n", traco);
		printf("\nLexema: <%s,%s>\n", lexema->tipo, lexema->valor);
	}

	return i;

	/*if (q == Q2) {
		return 1;
	}
	else {
		return 0;
	}*/
}

void AFD_linguagem(Lexema *lexema) {
	char value[50];
	strcpy(value, lexema->valor);

	if (strcmp(value, "if") == 0 || strcmp(value, "repeat") == 0 || strcmp(value, "until") == 0 ||
		strcmp(value, "end") == 0 || strcmp(value, "write") == 0 || strcmp(value, "read") == 0) {
			strcpy(lexema->tipo, "Reservado");
		}
}

int eh_simbolo(char c) {
	if (strchr("+-*/;=>", c) != NULL) { // c in "+-*/;=>"
		return 1;
	}
	else {
		return 0;
	}
}

int AFD_simbolos(char* cadeia, int verbose, int i, Lexema *lexema, int *k) {

	char traco[1000] = "";

	//Lexema lexema;
	Estado q = Q0;
	if (verbose) {
		strcat(traco, "Q0");
	}

	char c = cadeia[i];
	if (eh_simbolo(c)) {
		lexema->tipo[0] = c; // (*lexema).tipo[0] = c;
		lexema->tipo[1] = '\0';

		lexema->valor[0] = c;
		lexema->valor[1] = '\0';
		i = i + 1; // Estratégia lookahead;
		*k = *k + 1;
		
		q = Q1;
		if (verbose) {
			strcat(traco, "->Q1");
		}
	}
	else {
		q = QLixo;
		if (verbose) {
			strcat(traco, "->QLixo");
		}
	}

	if (verbose) {
		printf("\nTraco: %s\n", traco);
		printf("\nLexema: <%s,%s>\n", lexema->tipo, lexema->valor);
	}

	return i;

}

int AFD_naturais(char* cadeia, int verbose, int i, Lexema *lexema, int *k) {

	char traco[1000] = "";

	Estado q = Q0;
	if (verbose) {
		strcat(traco, "Q0");
	}

	char c = cadeia[i];
	if (!eh_digito(c)) {
		q = QLixo;
		if (verbose) {
			strcat(traco, "->QLixo");
		}
	}
	else {
		strcpy(lexema->tipo, "Natural");

		int i_lexema = 0;

		lexema->valor[i_lexema] = c;
		i_lexema = i_lexema + 1;

		q = Q1;
		if (verbose) {
			strcat(traco, "->Q1");
		}
		i = i + 1;
		for (/*i = 1*/; q != Q2; i++) {
			c = cadeia[i]; // i-ésimo caractere

			if (eh_digito(c)) {
				q = Q1;
				if (verbose) {
					strcat(traco, "->Q1");
				}
				lexema->valor[i_lexema] = c;
				i_lexema = i_lexema + 1;

			}
			else {
				q = Q2;
				if (verbose) {
					strcat(traco, "->Q2");
				}
				i = i - 1;
				//break;
			}
		}
		lexema->valor[i_lexema] = '\0';
		*k = *k + 1;
	}

	if (verbose) {
		printf("\nTraco: %s\n", traco);
		printf("\nLexema: <%s,%s>\n", lexema->tipo, lexema->valor);
	}

	return i;

}

int AFD_pascal(char* cadeia, int verbose, int i, Lexema *lexema, int *k) {

	char traco[1000] = "";

	Estado q = Q0;
	if (verbose) {
		strcat(traco, "Q0");
	}

	char c = cadeia[i];
	if (c == ':') {
		q = Q1;
		i++;
		c = cadeia[i];
		if (c == '=') {
			q = Q2;
			strcpy(lexema->tipo, "Pascal");
			lexema->valor[0] = cadeia[i-1];
			lexema->valor[1] = cadeia[i];
			lexema->valor[2] = '\0';
			i++;
			*k = *k + 1;
		}
		else {
			q = QLixo;
			if (verbose) {
				strcat(traco, "->QLixo");
			}
			i--;
		}
	}
	else {
		q = QLixo;
		if (verbose) {
			strcat(traco, "->QLixo");
		}
	}

	if (verbose) {
		printf("\nTraco: %s\n", traco);
		printf("\nLexema: <%s,%s>\n", lexema->tipo, lexema->valor);
	}

	return i;

}

int AFD_comentarios(char* cadeia, int verbose, int i, Lexema *lexema, int *k) {

	char traco[1000] = "";

	//Lexema lexema;
	Estado q = Q0;
	if (verbose) {
		strcat(traco, "Q0");
	}

	char c = cadeia[i];
	if (c == '{') {
		q = Q1;
		strcpy(lexema->tipo, "Comentario");
		i++;
		int i_lexema = 0;

		c = cadeia[i];
		while (c != '}') {
			if (verbose) {
				strcat(traco, "->Q1");
			}
			lexema->valor[i_lexema] = c;
			i_lexema = i_lexema + 1;
			i++;
			c = cadeia[i];
		}

		i = i + 1; // Estratégia lookahead;
		*k = *k + 1;
		
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

	if (verbose) {
		printf("\nTraco: %s\n", traco);
		printf("\nLexema: <%s,%s>\n", lexema->tipo, lexema->valor);
	}

	return i;

}

void varredura(char* cadeia) {

	Lexema lexema[100];
	memset(lexema, 0, 100*sizeof(Lexema));
	int k = 0;

	for (int i = 0; cadeia[i] != '\0'; ) {

		if (cadeia[i] == ' ') {
			i = i + 1;
			continue;
		}


		i = AFD_ID(cadeia, 0, i, &lexema[k], &k);

		AFD_linguagem(&lexema[k-1]);

		i = AFD_simbolos(cadeia, 0, i, &lexema[k], &k);
		
		i = AFD_pascal(cadeia, 0, i, &lexema[k], &k);

		i = AFD_naturais(cadeia, 0, i, &lexema[k], &k);

		i = AFD_comentarios(cadeia, 0, i, &lexema[k], &k);


		/* Exercício 5: Conferir as restrições/definições da linguagem TINY
		* (pascalZIM) do livro do K. Louden e implementar um analisador
		* léxico para a mesma e avaliá-lo sobre o código de cálculo de
		* fatorial.
		*/

	}

	for(int j = 0; j < k; j++) 
		printf("\nLexema: <%s,%s>\n", lexema[j].tipo, lexema[j].valor);

}

int main() {
	char teste[100] = "if thiago = null then := repeat + end; {Comentarios entram aqui} 532 + 456";

	varredura(teste);

	/*bool aceita = AFD(teste, 1);

	if (aceita) {
		printf("A string %s eh aceita pelo AFD!", teste);
	}
	else {
		printf("A string %s nao eh aceita pelo AFD!", teste);
	}
	*/
}