#include <stdio.h>
#include <stdlib.h>

int recursiv (int demand, int* sizes, int nSize) {
    if (nSize == 0) return demand;

    int total = demand / sizes[nSize-1];
    demand %= sizes[nSize-1];
    int menor = demand;
    if (demand == 0) return total;

    for (int i = nSize - 1; i >= 0; i--) {
        int rec = recursiv(demand, sizes, i);
        if (rec < menor) menor = rec;
    }
    return total + menor;
}

int main (void) {
    int demand, nSizes, menor;

    scanf("%i %i", &demand, &nSizes);
    int sizes[nSizes];
    for (int i = 0; i < nSizes; i++) scanf("%i", &sizes[i]);

    menor = recursiv(demand, sizes, nSizes);
    printf("%i\n", menor);

    return 0;
}
