#include <stdio.h>
#include <time.h>

long long int sum (long long int n) {
    long long int i = 2, sumbin = 0;

    while (n / i > 0 || n % i >= i / 2) {
        //printf("%lld %lld %lld ",n,i,n/i);
        //printf("i = %lld\n", i);
        long long int idiv = i/2;
        sumbin += ((n / i) * idiv);
        //printf("SumbinInicial = %lld\n", sumbin);
        long long int mod = n % i;
        long long int rest = mod / idiv;
        //printf("Rest = %lld\n", rest);
        if (rest > 0) sumbin += rest + (mod % idiv);
        i *= 2;
        //printf("SumbinFinal = %lld\n", sumbin);
    }
    //printf("\n");
    return sumbin;
}

int main () {
    long long int x, y;
    int sumb = 0;
    scanf("%lld", &x);
    scanf("%lld", &y);

    //printf("%lld\n", sum(y));
    //printf("%lld\n", sum(x));
    //sum(y);
    //sum(x);

    printf("%lld", sum(y) - (sum(x - 1)));
}


