#include <stdio.h>
#include <stdlib.h>

int minPackages(int demand, int* sizes, int nSize) {
    int* dp = (int*)malloc((demand + 1) * sizeof(int));
    for (int i = 0; i <= demand; i++) dp[i] = demand + 1;
    dp[0] = 0;

    for (int i = 1; i <= demand; i++) {
        for (int j = 0; j < nSize; j++) {
            if (sizes[j] <= i) {
                dp[i] = dp[i] < dp[i - sizes[j]] + 1 ? dp[i] : dp[i - sizes[j]] + 1;
            }
        }
    }

    int result = dp[demand] > demand ? -1 : dp[demand];
    free(dp);
    return result;
}

int main(void) {
    int demand, nSizes;

    scanf("%i %i", &demand, &nSizes);
    int sizes[nSizes];
    for (int i = 0; i < nSizes; i++) scanf("%i", &sizes[i]);

    int result = minPackages(demand, sizes, nSizes);
    printf("%i\n", result);

    return 0;
}
