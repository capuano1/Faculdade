#include <stdio.h>
#include <stdlib.h>

// Editar para retornar o vetor ordenado ao invés do número de inversões

// Mesclar metades ordenadas e fazer contagem
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

int main() {

}