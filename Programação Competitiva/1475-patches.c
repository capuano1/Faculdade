#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int merge(int arr[], int temp[], int left, int mid, int right) {
    int i = left;
    int j = mid;
    int k = left;
    int inv_count = 0;

    while (i <= mid - 1 && j <= right) {
        if (arr[i] <= arr[j]) {
            temp[k] = arr[i];
            k++; i++;
        } else {
            temp[k] = arr[j];
            k++; j++;
            inv_count += (mid - i);
        }
    }

    while (i <= mid - 1) {
        temp[k] = arr[i];
        k++; i++;
    }
    while (j <= right) {
        temp[k] = arr[j];
        k++; j++;
    }
    for (int l = left; l <= right; l++) {
        arr[l] = temp[l];
    }

    return inv_count;
}

int mergeSort(int arr[], int temp[], int left, int right) {
    int mid, inv_count = 0;
    if (right > left) {
        mid = (left + right) / 2;
        inv_count += mergeSort(arr, temp, left, mid);
        inv_count += mergeSort(arr, temp, mid + 1, right);
        inv_count += merge(arr, temp, left, mid + 1, right);
    }
    return inv_count;
}

int reparo_unico(int P[], int i, int j, int remendo1, int remendo2) {
    if (i == j) {
        if (remendo1 < remendo2) return remendo1;
        else return remendo2;
    }

    int comprimento = P[j] - P[i];

    if (comprimento > remendo1 && comprimento > remendo2) {
        return 99999999;
    }

    int custo = 99999999;

    if (remendo1 >= comprimento) {
        if (remendo1 < custo) custo = remendo1;
    }
    if (remendo2 >= comprimento) {
        if (remendo2 < custo) custo = remendo2;
    }

    return custo;
}

int solve(int N, int C, int remendo1, int remendo2, int array[]) {
    // ordena os furos
    mergeSort(array, (int *)malloc(N * sizeof(int)), 0, N - 1);

    // para tratar do circulo
    int dobrado[2 * N];
    for (int i = 0; i < N; i++) {
        dobrado[i] = array[i];
        dobrado[i + N] = (int)array[i] + C;
    }

    int pd[2 * N][2 * N];

    // valor alto para sempre encontrar um menor caso seja possível
    memset(pd, 99999999, (2*N)*(2*N)*sizeof(int));

    // minimo, tampa apenas 1 furo
    for (int i = 0; i < 2 * N; i++) {
        if (remendo1 < remendo2) pd[i][i] = remendo1;
        else pd[i][i] = remendo2;
    }

    for (int L = 2; L <= N; L++) {
        for (int i = 0; i < 2 * N - L + 1; i++) {
            // ultimo furo
            int j = i + L - 1;

            // cobrir tudo com 1 remendo
            int custo_unico = reparo_unico(dobrado, i, j, remendo1, remendo2);
            pd[i][j] = custo_unico;

            // dividir
            for (int k = i; k < j; k++) {
                // se algum subproblema tiver o valor maximo, ele é impossivel
                if (pd[i][k] != 99999999 && pd[k + 1][j] != 99999999) {
                    if (pd[i][k] + pd[k + 1][j] < pd[i][j]) pd[i][j] = pd[i][k] + pd[k + 1][j];
                }
            }
        }
    }

    // encontrar o menor custo para preencher todos os furos
    int custo_minimo = 99999999;
    for (int i = 0; i < N; i++) {
        if (pd[i][i + N - 1] < custo_minimo) custo_minimo = pd[i][i + N - 1];
    }

    return custo_minimo;
}

int main() {
    int N, C, remendo1, remendo2;

    while (scanf("%i %i %i %i", &N, &C, &remendo1, &remendo2) != EOF) {
        int array[N];
        for (int i = 0; i < N; i++) {
            scanf("%i", &array[i]);
        }

        int resultado = solve(N, C, remendo1, remendo2, array);
        printf("%i\n", resultado);
    }

    return 0;
}