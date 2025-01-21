#include <stdio.h>
#include <stdlib.h>

int recursiv (int demand, int* sizes, int nSize) {
    int total = demand / sizes[nSize-1];
    demand %= sizes[nSize-1];
    int menor = demand;
    if (demand == 0) return total;
    for (; nSize > 1; nSize--) {
        int rec = recursiv(demand, sizes, nSize-1);
        if (rec < menor && rec != 0) menor = rec;
    }
    return total + menor;
}

int main (void) {
    int demand, nSizes, total, menor;

    scanf("%i %i", &demand, &nSizes);
    int sizes[nSizes];
    menor = demand;
    for (int i = 0; i < nSizes; i++) scanf("%i", &sizes[i]);
    for (int i = nSizes; i > 0; i--) {
        int res = recursiv(demand, sizes, nSizes);
        if (res < menor) menor = res;
    }
    printf("%i", menor);
}