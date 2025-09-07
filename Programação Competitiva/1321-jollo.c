#include <stdio.h>

int encontraMenor(int prince[2], int princess[3], int menor) {
    for (int i = 0; i < 5; i++) {
        if (i < 3) {
            if (menor == princess[i]) {
                menor++;
                i = 0;
                continue;
            }
        }
        else {
            if (menor == prince[i - 3]) {
                menor++;
                i = 0;
                continue;
            }
        }
    }
    if (menor > 52) menor = -1;
    return menor;
}

int main() {
 
    int prince[2], princess[3];
    FILE *ans = fopen("ans.txt", "w");
    
    scanf("%i %i %i %i %i", &princess[0], &princess[1], &princess[2], &prince[0], &prince[1]);
    while (princess[0] != 0) {
        for (int i = 3; i > 0; i--) {
            for (int j = 0; j < i-1; j++) {
                if (princess[j] > princess[j+1]) {
                    int aux = princess[j+1];
                    princess[j+1] = princess[j];
                    princess[j] = aux;
                }
            }
        }
        if (prince[0] > prince[1]) {
            int aux = prince[1];
            prince[1] = prince[0];
            prince[0] = aux;
        }
        
        /*
        Para o caso da maior carta do principe ser maior do que a maior carta da princesa,
        sabemos que 1 rodada o principe irá ganhar, então precisamos pensar na segunda.
        Aqui, podemos observar 2 possibilidades:
        1. A segunda carta do principe ser maior do que a primeira carta da princesa
        2. A segunda carta do principe não ser maior do que a primeira carta da princesa
        No caso da possibilidade 1, podemos retornar a menor carta possível, no caso, 1, se
        ninguém tiver ela em mãos. No caso da possibilidade 2, temos mais duas possibilidades:
        a. A segunda carta do principe perder para a segunda carta da princesa
        b. A segunda carta do principe não perder para a segunda carta da princesa
        No caso da possibilidade a., devemos retornar o próximo maior número após a primeira
        carta da princesa. No caso da possibilidade b., devemos retornar o próximo maior
        número após a segunda carta da princesa
        */
        if (prince[1] > princess[2]) {
            if (prince[0] > princess[2]) {
                int menor = encontraMenor(prince, princess, 1);
                printf("%i\n", menor);
                fprintf(ans, "%i\n", menor);
            }
            else {
                if (prince[0] < princess[1]) {
                    int menor = encontraMenor(prince, princess, princess[2]);
                    printf("%i\n", menor);
                    fprintf(ans, "%i\n", menor);
                }
                else {
                    int menor = encontraMenor(prince, princess, princess[1]);
                    printf("%i\n", menor);
                    fprintf(ans, "%i\n", menor);
                }
            }
        }
        
        /*
        Agora, caso a maior carta do principe não seja maior do que a maior carta da princesa, temos
        duas possibilidades:
        1. A segunda maior carta do principe também ser menor do que a segunda carta da princesa
        2. A segunda maior carta do principe ser maior do que a segunda carta da princesa
        No caso 1, é simples: o principe perde. No caso 2, devemos retornar a próxima maior carta
        acima da segunda carta da princesa (logicamente, a princesa iria descartar sua menor carta,
        fazendo com que a segunda maior dela sobre, então é exatamente esta que devemos bater)
        */
        else {
            if (prince[0] < princess[1]) {
                printf("-1\n");
                fprintf(ans, "-1\n");
            }
            else {
                int menor = encontraMenor(prince, princess, princess[1]);
                printf("%i\n", menor);
                fprintf(ans, "%i\n", menor);
            }
        }
        scanf("%i %i %i %i %i", &princess[0], &princess[1], &princess[2], &prince[0], &prince[1]);
    }
    return 0;
}