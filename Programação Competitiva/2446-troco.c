#include <stdio.h>
#include <stdbool.h>

bool pode_pagar(int soma_alvo, int moedas[], int n) {
    // Cria uma tabela de programação dinâmica. A tabela `dp` armazena
    // se um valor específico pode ser alcançado.
    bool dp[soma_alvo + 1];
    
    // Inicializa a tabela. O valor 0 sempre pode ser alcançado (não usando nenhuma moeda).
    for (int i = 0; i <= soma_alvo; i++) {
        dp[i] = false;
    }
    dp[0] = true;

    // Itera sobre cada moeda disponível
    for (int i = 0; i < n; i++) {
        // Para cada moeda, atualiza a tabela `dp` de trás para frente.
        // Isso evita usar a mesma moeda várias vezes na mesma combinação.
        for (int j = soma_alvo; j >= moedas[i]; j--) {
            // Se o valor (j - moedas[i]) era alcançável, então o valor j também é.
            dp[j] = dp[j] || dp[j - moedas[i]];
        }
    }

    // Retorna se o valor final da compra (`soma_alvo`) é alcançável.
    return dp[soma_alvo];
}

int main() {
    int valor_compra, num_moedas;

    // Lê os valores de V e M da entrada padrão
    scanf("%d %d", &valor_compra, &num_moedas);

    // Declara um array para armazenar as moedas
    int moedas[num_moedas];

    // Lê os M valores das moedas
    for (int i = 0; i < num_moedas; i++) {
        scanf("%d", &moedas[i]);
    }

    // Chama a função para verificar se é possível pagar e imprime o resultado
    if (pode_pagar(valor_compra, moedas, num_moedas)) {
        printf("S\n");
    } else {
        printf("N\n");
    }

    return 0;
}