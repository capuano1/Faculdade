#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double lanc (double h, double alfa, double v) {
    alfa = alfa * 3.14159 / 180.0;
    double vs = v * sin(alfa);
    double vc = v * cos(alfa);
    return (vc / 9.80665) * (vs + sqrt(vs * vs + 2 * 9.80665 * h));
}

int main () {
    double h, p1, p2, alfa, v;
    while (scanf("%lf", &h) != EOF) {
        scanf("%lf %lf", &p1, &p2);
        int n;
        scanf("%d", &n);
        for (int i = 0; i < n; i++) {
            scanf("%lf %lf", &alfa, &v);
            double alcance = lanc(h, alfa, v);
            if (alcance >= p1 && alcance <= p2) {
                printf("%.5f -> DUCK\n", alcance);
            } else {
                printf("%.5f -> NUCK\n", alcance);
            }
        }
    }
}