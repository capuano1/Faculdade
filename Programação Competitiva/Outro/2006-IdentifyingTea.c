#include <stdio.h>

// Exercício teste nao pedido em Programação Competitiva
// Para testar problemas do Beecrowd

int main() {
 
    int tea, read, count = 0;
    scanf("%i", &tea);
    for (int i = 0; i < 5; i++) {
        scanf("%i", &read);
        if (read == tea) count++;
    }
    printf("%i", count);
 
    return 0;
}