#include <stdio.h>

int dif_mod(int a, int b) {
    if (a > b) return a - b;
    return b - a;
}

int main() {
 
    int x1, y1, x2, y2, difx, dify;

    scanf("%i %i %i %i", &x1, &y1, &x2, &y2);

    while (x1 != 0 && y1 != 0 && x2 != 0 && y2 != 0) {
        difx = dif_mod(x1, x2);
        dify = dif_mod(y1, y2);

        if (x1 == x2 && y1 == y2) {
            printf("0\n");
        } else if (difx == dify) {
            printf("1\n");
        } else if (x1 == x2 || y1 == y2) {
            printf("1\n");
        } else {
            printf("2\n");
        }
        scanf("%i %i %i %i", &x1, &y1, &x2, &y2);
    }
 
    return 0;
}