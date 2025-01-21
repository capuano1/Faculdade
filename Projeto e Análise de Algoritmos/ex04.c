#include <stdio.h>
#include <stdlib.h>

int main (void) {
    int demand, nSizes, total, menor;

    scanf("%i %i", &demand, &nSizes);
    int sizes[nSizes];
    menor = demand;
    for (int i = 0; i < nSizes; i++) scanf("%i", &sizes[i]);
    int upSize = nSizes - 1;

    while (upSize > 0) {
        total = 0;
        int origDemand = demand;
        int isFirst = 1;
        for (int i = upSize; i >= 0; i--) {
            if (origDemand/sizes[i] == 0 && isFirst) {
                upSize--;
                continue;
            }
            isFirst = 0;
            total += origDemand / sizes[i];
            origDemand = origDemand % sizes[i];
        }
        if (total < menor && total != 0) menor = total;
        upSize--;
    }
    printf("%i", menor);
}