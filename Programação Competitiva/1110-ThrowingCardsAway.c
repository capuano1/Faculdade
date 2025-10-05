#include <stdio.h>
#include <stdlib.h>

int main (void) {
    int n;

    scanf("%i", &n);

    // Não interessa mover as cartas para o fim, elas sempre estarão na mesma ordem (considerando as retiradas).
    // Melhor trabalhar com um esquema circular.
    while (n != 0) {
        if (n == 1) {
            printf("Discarded cards: \n");
            printf("Remaining card: 1\n");
            scanf("%i", &n);
            continue;
        }
        int cartas[n];
        int removidas[n-1];
        for (int i = 1; i <= n; i++) cartas[i-1] = i;

        int remainingCards = n, i = 0;
        /*
        Lógica: Este while vai sempre ficar repetindo, realizando as operações na ordem em que o exercício pediu:
        Primeiro vamos remover uma carta, depois vamos mover ela para o final (não fazer nada pois trabalhando com
        esquema circular, acaba dando na mesma). Caso uma carta seja removida, seu valor é alterado para -1 e ela é
        guardada no array removidas.
        */
        while(remainingCards != 1) {
            // Procurar uma carta que ainda esteja no baralho, ou seja, não seja -1
            while(cartas[i] == -1) if (i + 1 >= n) i = 0; else i++;
            // Remove a carta e adiciona ela no array de removidas, além de atualizar o inteiro que guarda quantas
            // cartas ainda restam no baralho (devemos parar quando houver apenas 1)
            removidas[n - remainingCards] = cartas[i];
            cartas[i] = -1;
            remainingCards--;
            // Novamente vamos procurar a próxima carta que ainda esteja no baralho
            while(cartas[i] == -1) if (i + 1 >= n) i = 0; else i++;
            /*
            Aqui nós já encontramos uma carta válida no baralho e, caso ela seja a última carta, fazemos um break
            já tendo o i no índice correto da carta restante, para realizar o print.
            Este código está correto pois para o remainingCards chegar aqui com valor inferior à 1, como 0, 
            seria necessário que ele estivesse em 1 ao ser removido anteriormente, o que significaria que num
            ciclo anterior ele passou por aqui sendo 1, porém, se isso tivesse ocorrido, este if teria realizado o break.
            Portanto, seria um absurdo chegar um valor de remainingCards < 1 neste pedaço.
            */
            if (remainingCards == 1) break;
            // Caso ela não seja a última carta, apenas pulamos para o próximo i e deixamos o ciclo recomeçar.
            if (i + 1 >= n) i = 0; else i++;
        }
        printf("Discarded cards: ");
        for (int j = 0; j < n-1-1; j++) printf("%i, ", removidas[j]);
        printf("%i\n", removidas[n-1-1]);
        printf("Remaining card: %i\n", cartas[i]);
        scanf("%i", &n);
    }
}