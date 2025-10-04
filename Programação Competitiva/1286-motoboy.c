#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int time;
    int pizzas;
} Entregas;

int main(void) {
    int N, P;

    scanf("%i", &N);

    while (N != 0) {
        Entregas ent[N];
        
        scanf("%i", &P);

        int dp[P+1];
        // Preencher tudo com zero, já que precisamos maximizar
        memset(dp, 0, (P + 1)*sizeof(int));

        for (int i = 0; i < N; i++) scanf("%i %i", &ent[i].time, &ent[i].pizzas);

        for (int i = 0; i < N; i++) {
            // Precisa rodar ao contrário, senão pode acabar duplicando os pedidos na hora de somar
            // Indo na ordem normal, por exemplo, você adiciona o pedido em j = 2 e acaba duplicando em j = 4
            // Pois ele testa para ver se j = 4 < j = (4 - 2) + tempo de entrega, o que faz com que o pedido
            // seja considerado 2 vezes. 
            for (int j = P + 1; j >= ent[i].pizzas; j--) {
                // Testa para ver se o valor que está atualmente em dp é maior do que seria somando
                // a entrega das pizzas selecionadas além desta (j - ent[i].pizzas) com esta
                // Básico da Programação Dinâmica
                //printf("%i %i\n", dp[j], (dp[j - ent[i].pizzas] + ent[i].time));
                if (dp[j] < (dp[j - ent[i].pizzas] + ent[i].time)) dp[j] = dp[j - ent[i].pizzas] + ent[i].time;
                //printf("%i\n", dp[j]);
                //printf("%i\n", j);
            }
            //for (int j = 0; j <= P+1; j++) printf("%i ", dp[i]);
            //printf("\n");
        }

        int best = 0;
        for (int i = 0; i < P + 1; i++) if (dp[i] > best) best = dp[i];

        printf("%i min.\n", best);
    
        scanf("%i", &N);
    }
}