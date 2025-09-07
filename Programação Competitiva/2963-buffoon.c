#include <stdio.h>
 
int main() {
 
    int candidates, carlos, aux;
    scanf("%i", &candidates);
    scanf("%i", &carlos);
    for (int i = 1; i < candidates; i++) {
        scanf("%i", &aux);
        if (aux > carlos) {
            printf("N\n");
            return 0;
        }
    }
    printf("S\n");
    return 0;
}