#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Fazendo uma struct para facilitar, assim ele sempre cria uma cópia quando enviado por parâmetro.
typedef struct {
    int array[6];
} estoque;

int decode (char* size) {
    if (strcmp(size, "XS") == 0) return 0;
    else if (strcmp(size, "S") == 0) return 1;
    else if (strcmp(size, "M") == 0) return 2;
    else if (strcmp(size, "L") == 0) return 3;
    else if (strcmp(size, "XL") == 0) return 4;
    else if (strcmp(size, "XXL") == 0) return 5;
    else return -1;
}

int backtrack (estoque arrayCamisetas, int volunt, int tamanhos[][2]) {
    if (volunt == -1) return 1;

    if (arrayCamisetas.array[tamanhos[volunt][0]] - 1 >= 0) {
        arrayCamisetas.array[tamanhos[volunt][0]] -= 1;
        if (backtrack(arrayCamisetas, volunt-1, tamanhos)) return 1;
        arrayCamisetas.array[tamanhos[volunt][0]] += 1;
    }
    if (arrayCamisetas.array[tamanhos[volunt][1]] - 1 >= 0) {
        arrayCamisetas.array[tamanhos[volunt][1]] -= 1;
        if (backtrack(arrayCamisetas, volunt-1, tamanhos)) return 1;
        arrayCamisetas.array[tamanhos[volunt][1]] += 1;
    }
    return 0;
}

int main () {
    int tests;
    scanf("%i", &tests);

    for (int i = 0; i < tests; i++) {
        int camisetas, volunt;
        estoque arrayCamisetas;
        scanf("%i %i", &camisetas, &volunt);
        int tamanhos[volunt][2];

        for (int j = 0; j < 6; j++) {
            arrayCamisetas.array[j] = (camisetas/6);
        }

        for (int j = 0; j < volunt; j++) {
            char option1[5], option2[5];
            scanf("%s %s", option1, option2);
            tamanhos[j][0] = decode(option1);
            tamanhos[j][1] = decode(option2);
        }

        int result = backtrack(arrayCamisetas, volunt-1, tamanhos);
        if (result) printf("YES\n");
        else printf("NO\n");

    }
}