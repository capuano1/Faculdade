#include <stdio.h>

int main() {
 
    int nalice, nbetty;
    
    scanf("%i %i", &nalice, &nbetty);
    while(nalice != 0 && nbetty != 0) {
        
        int card_alice[nalice], card_betty[nbetty];
        int unique_alice = 0, unique_betty = 0;
        
        for (int i = 0; i < nalice; i++) {
            scanf("%i", &card_alice[i]);
        }
        for (int i = 0; i < nbetty; i++) {
            scanf("%i", &card_betty[i]);
        }

        for (int i = 0; i < nalice; i++) {
            int found = 0;
            if (i > 0) {
                if (card_alice[i] == card_alice[i-1]) {
                    continue;
                }
            }
            for (int j = 0; j < nbetty; j++) {
                if (card_alice[i] == card_betty[j]) {
                    found = 1;
                    break;
                }
                if (card_alice[i] < card_betty[j]) {
                    break;
                }
            }
            if (!found) {
                unique_alice++;
            }
        }
        for (int i = 0; i < nbetty; i++) {
            int found = 0;
            if (i > 0) {
                if (card_betty[i] == card_betty[i-1]) {
                    continue;
                }
            }
            for (int j = 0; j < nalice; j++) {
                if (card_betty[i] == card_alice[j]) {
                    found = 1;
                    break;
                }
                if (card_betty[i] < card_alice[j]) {
                    break;
                }
            }
            if (!found) {
                unique_betty++;
            }
        }

        if (unique_alice < unique_betty) {
            printf("%i\n", unique_alice);
        } else {
            printf("%i\n", unique_betty);
        }
        
        scanf("%i %i", &nalice, &nbetty);

    }
 
    return 0;
}