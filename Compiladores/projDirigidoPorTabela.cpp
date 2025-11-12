// 
// proAFD_simples.cpp : Este arquivo contém a função 'main'. A execução do programa começa e termina ali.
//

#include <cstdio> // stdio.h
#include <string> // string.h

// Estados do AFD
typedef enum { Q0, Q1, Q2, QLixo } Estado;
typedef enum { LETRA, DIGITO, OUTRA } Categoria;
//typedef enum {false, true} bool;

#define NEstados 4
#define NCategorias 3

static Estado delta[NEstados][NCategorias];
static bool	  avanca[NEstados][NCategorias];
static bool	  aceita[NEstados];

void inicializa() {
	for (int i = 0; i < NEstados; i++)
		for (int j = 0; j < NCategorias; j++) {
			delta[i][j] = QLixo;
			avanca[i][j] = false; // 0
		}

	for (int i = 0; i < NEstados; i++) aceita[i] = false;

	delta[Q0][LETRA]  = Q1; // Q0 + LETRA -> Q1
	delta[Q1][LETRA]  = Q1; // Q1 + LETRA -> Q1
	delta[Q1][DIGITO] = Q1; // Q1 + DIGITO -> Q1
	delta[Q1][OUTRA]  = Q2;  // Q1 + OUTRA -> Q2


	avanca[Q0][LETRA]  = true; // Q0 + LETRA -> Q1
	avanca[Q1][LETRA]  = true; // Q1 + LETRA -> Q1
	avanca[Q1][DIGITO] = true; // Q1 + DIGITO -> Q1

	aceita[Q2] = true; // Q2 é o único estado de aceitação
}


// Função para verificar se um dado caracter c é 
// um caracter alfabético: [a-zA-Z]
bool eh_letra(char c) {
	if (((c >= 'a') && (c <= 'z')) || ((c >= 'A') && (c <= 'Z'))) {
		return true;
	}

	return false;
}

// Função para verificar se um dado caracter c é 
// um caracter numérico: [0-9]
bool eh_digito(char c) {
	if ((c >= '0') && (c <= '9')) {
		return true;
	}

	return false;
}

Categoria get_categoria(char c) {
	if (eh_digito(c)) return DIGITO;

	if (eh_letra(c)) return LETRA;

	return OUTRA;
}

// Programação do autômato
// [a-zA-Z]([a-zA-Z0-9]*)
int AFD_ID(char* cadeia, bool verbose, int i) {

	char traco[1000] = "",
		 c;

	Estado q = Q0;
	Categoria cat;

	do {
		c = cadeia[i];
		cat = get_categoria(c);

		q = delta[q][cat];

	} while ((q != QLixo) && // O estado ATUAL não for LIXO
		(!aceita[q]) && // O processamento não acabou (q != Q2)
		(avanca[q][get_categoria(cadeia[++i])])); // O próximo caractere é interessante para a construção do lexema

	/* última atualização de estados*/
	c = cadeia[i];
	cat = get_categoria(c);
	q = delta[q][cat];

	/* Agora conferimos se o estado final é de aceitação ou se é lixo */


	if (aceita[q]) {
		printf("Aceita");
	}
	else {
		printf("Rejeita");
		i--;
	}

	return i;

}

bool eh_simbolo(char c) {
	if (strchr("+-*/;=>", c) != NULL) { // c in "+-*/;=>"
		return true;
	}
	else {
		return false;
	}
}

/*int AFD_simbolos(char* cadeia, bool verbose, int i, Lexema* lexema, int* k) {


}
*/

int main() {

	inicializa();

	char cadeia[100] = "x10";

	int i = AFD_ID(cadeia, true, 0);
}