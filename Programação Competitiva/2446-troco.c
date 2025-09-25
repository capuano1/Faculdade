#include <stdio.h>
#include <string.h>

int testa_moedas(int soma_alvo, int moedas[], int n) {
    
    int troco[soma_alvo + 1];
    
    memset(troco, 0, (soma_alvo + 1)*sizeof(int));
    troco[0] = 1;

    // Cada moeda
    for (int i = 0; i < n; i++) {
        // Quais valores ela resolve (restante = 0)
        for (int j = soma_alvo; j >= moedas[i]; j--) {
            if (troco[j] == 1 || troco[j - moedas[i]] == 1) troco[j] = 1;
            // Não precisa de else, memset já colocou tudo em 0
        }
    }

    return troco[soma_alvo];
}

int main() {
    
    int compra, nMoedas;

    scanf("%d %d", &compra, &nMoedas);
    int moedas[nMoedas];
    
    for (int i = 0; i < nMoedas; i++) {
        scanf("%d", &moedas[i]);
    }

    int result = testa_moedas(compra, moedas, nMoedas);
    if (result) printf("S\n");
    else printf("N\n");

    return 0;
}