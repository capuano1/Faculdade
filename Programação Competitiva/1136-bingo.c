#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 
int main() {
 
    int n = 1, b = 1, count;
    /*
    IDEIA BASICA
    O count serve como um contador, para ver se eu encontrei todos os números necessários 
    do intervalo. Ele começa em n+1 pois eu decidi verificar que ele deverá ser 0 ao final
    para significar que todos os valores foram encontrados.
    ballbool é um array basicamente booleano, indicando se eu fui capaz de encontrar uma
    forma de conseguir o valor do índice do array como uma combinação entre duas bolas.
    balls é um array que salva quais são as bolas presentes na jogada.
    Primeiramente, há uma lógica de eliminação dos números das próprias bolas para caso
    haja uma bola 0 na jogada. É verificado se a variável "zero" é true ou false (1 ou 0).
    Caso ela seja false, eu desconsidero a lógica feita e reseto o contador e o array
    */
    
    scanf("%i %i", &n, &b);
    while(n != 0 && b != 0) {
        count = n + 1;
        int balls[b], ballbool[n+1];
        memset(ballbool, 0, sizeof(ballbool));
        int zero = 0;
        
        // Escaneia as bolas e faz a verificação de eliminação dos números das próprias bolas
        for (int i = 0; i < b; i++) {
            scanf("%i", &balls[i]);
            if (balls[i] == 0) zero = 1;
            if (ballbool[balls[i]] == 0) {
                ballbool[balls[i]] = 1;
                count--;
            }
        }
        
        // Caso não haja uma bola 0 na jogada, o contador e o ballbool são resetados
        // É necessário por conta da lógica de eliminação dos números das próprias bolas
        if (!zero) {
            count = n + 1;
            memset(ballbool, 0, sizeof(ballbool));
        }
        
        // Eliminação da combinação 0, pois ela sempre é possível por conta de haver
        // reposição das bolas. Com isso, uma combinação de um número com ele mesmo
        // sempre será 0.
        if (ballbool[0] == 0) {
            ballbool[0] = 1;
            count--;
        }
        
        // Força bruta, encontrar todas as combinações enquanto o count ainda é maior do que 0
        for (int i = 0; i < b - 1 && count > 0; i++) {
            for (int j = i + 1; j < b && count > 0; j++) {
                int res = abs(balls[i] - balls[j]);
                if (ballbool[res] == 0) {
                    ballbool[res] = 1;
                    count--;
                }
            }
        }
        if (count == 0) printf("Y\n");
        else printf("N\n");
        //printf("%i", count);
        scanf("%i %i", &n, &b);
    }
 
    return 0;
}