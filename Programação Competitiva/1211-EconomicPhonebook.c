#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Merge Sort usado em outros exercícios, adaptado para as necessidades deste exercício (números como string)
void merge(char arr[][205], char temp[][205], int left, int mid, int right) {
    int i = left;
    int j = mid;
    int k = left;

    while (i <= mid - 1 && j <= right) {
        if (strcmp(arr[i], arr[j]) < 0) {
            strcpy(temp[k], arr[i]);
            k++; i++;
        } else {
            strcpy(temp[k], arr[j]);
            k++; j++;
        }
    }

    while (i <= mid - 1) {
        strcpy(temp[k], arr[i]);
        k++; i++;
    }
    while (j <= right) {
        strcpy(temp[k], arr[j]);
        k++; j++;
    }
    for (int l = left; l <= right; l++) {
        strcpy(arr[l], temp[l]);
    }
}

// Divide
void mergeSort(char arr[][205], char temp[][205], int left, int right) {
    int mid;
    if (right > left) {
        mid = (left + right) / 2;
        // Esquerda
        mergeSort(arr, temp, left, mid);
        // Direita
        mergeSort(arr, temp, mid + 1, right);
        // Junta
        merge(arr, temp, left, mid + 1, right);
    }
}

int main(void) {
    int n;

    while (scanf("%i", &n) != EOF) {
        if (n == 1) {
            printf("0\n");
            continue;
        }
        int saved = 0;
        char numbers[n][205];

        for (int i = 0; i < n; i++) scanf("%s", numbers[i]);

        // Os telefones lidos precisam ser strings pois eles podem ter tamanho até 200 algarismos
        // Muito maior do que qualquer variável numérica disponível.
        char temp[n][205];
        // Merge Sort usado em vários outros exercícios mas adaptado para as necessidades deste.
        // Deixo ordenado pois, de maneira ordenada, o maior número de algarismos repetidos de acordo
        // com o solicitado pelo exercício aparecerá.
        mergeSort(numbers, temp, 0, n-1);

        // Vamos testar cada telefone. Começo em 1 pois vou testar i e i-1.
        // A ideia é ver quantos são iguais em relação ao número anterior.
        for (int i = 1; i < n; i++) {

            // Se o tamanho for diferente, eu terei de imprimir completamente o próximo número maior
            // Por isso, não há economia.
            if (strlen(numbers[i]) != strlen(numbers[i-1])) continue;
            // Aqui eu testo cada algarismo de ambos números até que haja uma diferença. Dessa forma eu
            // descubro as economias.
            for (int j = 0; j < strlen(numbers[i]); j++) {
                if (numbers[i][j] == numbers[i-1][j]) saved++;
                else break;
            }
        }
        printf("%i\n", saved);
    }
}