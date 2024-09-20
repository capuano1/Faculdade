#include <stdio.h>
//#include <math.h> não vamos usar aqui, porém é muito usada

//main é o primeiro comando a ser executado, o resto apenas se for chamado

int soma (int a, int b) {
    return a + b;
}

//implementar antes é bom pois alguns compiladores reclamam que você chama ela antes de implementar

void imprimaAloMundo () {
    printf("Alo Mundo.");
}

//void não tem retorno, por isso, não precisa de retorno no fim

int main () {
    int n1, n2, s;
    printf("Digite o primeiro número: ");
    scanf("%i", &n1);
    printf("\nDigite o segundo número: ");
    scanf("%i", &n2);
    s = soma(n1, n2);
    printf("A soma de %i com %i é %i", n1, n2, s);
    return 0;
}