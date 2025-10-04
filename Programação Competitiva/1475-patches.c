#include <stdio.h>
#include <stdlib.h>

// MergeSort utilizado em outros exercícios
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

// Divide
int mergeSort(int arr[], int temp[], int left, int right) {
    int mid, inv_count = 0;
    if (right > left) {
        mid = (left + right) / 2;
        // Esquerda
        inv_count += mergeSort(arr, temp, left, mid);
        // Direita
        inv_count += mergeSort(arr, temp, mid + 1, right);
        // Junta
        inv_count += merge(arr, temp, left, mid + 1, right);
    }
    return inv_count;
}

int solve(int holes[], int N, int C, int T1, int T2) {
    int i, start, best = 999999999;
    int extended[2*N];        // 2N para cobrir o círculo

    // temp usado na implementação do MergeSort
    int temp = malloc(N*sizeof(int));
    mergeSort(holes, temp, 0, N-1);
    free(temp);

    // Cria o array estendido (dobrado) para lidar com a natureza circular do problema
    for (i = 0; i < N; i++) {
        extended[i] = holes[i];         // Buracos originais
        extended[i+N] = holes[i] + C;   // Buracos considerando uma volta completa no pneu
    }

    // Testa cada buraco como se ele fosse o inicial, para verificação do círculo
    for (start = 0; start < N; start++) {
        // custo ACUMULADO para preencher os buracos
        int dp[2*N+1]; 
        
        // Inicializa com valor muito grande para que o primeiro resultado encontrado sempre seja menor
        // É como se inicializasse com um valor infinito, muito comum em Pesquisa Operacional
        for (i = 0; i <= 2*N; i++) dp[i] = 999999999;
        
        // Custo inicial 0 para o primeiro buraco
        dp[start] = 0;

        // Loop para começar do buraco inicial do for acima e andar por N buracos
        // Ou seja, faz uma volta completa (e apenas uma volta completa, não vai pegar o array completo)
        for (i = start; i < start + N; i++) {
            if (dp[i] == 999999999) continue;

            // Remendo 1
            int j = i;
            while (j < start + N && extended[j] <= extended[i] + T1) j++;
            
            if (dp[j] > dp[i] + T1) dp[j] = dp[i] + T1;

            // Remendo 2
            j = i;
            while (j < start + N && extended[j] <= extended[i] + T2) j++;
            
            if (dp[j] > dp[i] + T2) dp[j] = dp[i] + T2;
        }

        // Atualiza o melhor resultado se necessário
        if (best > dp[start + N]) best = dp[start + N];
    }
    
    return best;
}

int main() {
    int N, C, T1, T2;
    
    while (scanf("%d %d %d %d", &N, &C, &T1, &T2) != EOF) {
        
        int holes[N]; 
        
        for (int i = 0; i < N; i++) scanf("%d", &holes[i]);
        
        printf("%d\n", solve(holes, N, C, T1, T2));
    }
    return 0;
}