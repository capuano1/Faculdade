#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Função para trocar dois elementos de posição
void swap(char** a, char** b) {
    char* temp = *a;
    *a = *b;
    *b = temp;
}

// Função para fazer o heapify em uma subárvore enraizada em um nó i
void heapify(char** arr, int n, int i, int* index) {
    int largest = i;
    int l = 2*i + 1;
    int r = 2*i + 2;

    while (1) {
        // Compara a string apontada por arr[l] com a string apontada por arr[largest]
        while (l < n && index[(int)arr[l][0]] == index[(int)arr[largest][0]]) {
            int j = 1;
            while (arr[l][j] == arr[largest][j] && j < strlen(arr[l])) {
                j++;
            }
            if (j < strlen(arr[l]) && arr[l][j] < arr[largest][j]) {
                largest = l;
            }
            l++;
        }
        if (l < n && index[(int)arr[l][0]] < index[(int)arr[largest][0]]) {
            largest = l;
        }

        // Compara a string apontada por arr[r] com a string apontada por arr[largest]
        while (r < n && index[(int)arr[r][0]] == index[(int)arr[largest][0]]) {
            int j = 1;
            while (arr[r][j] == arr[largest][j] && j < strlen(arr[r])) {
                j++;
            }
            if (j < strlen(arr[r]) && arr[r][j] < arr[largest][j]) {
                largest = r;
            }
            r++;
        }
        if (r < n && index[(int)arr[r][0]] < index[(int)arr[largest][0]]) {
            largest = r;
        }

        if (largest != i) {
            swap(&arr[i], &arr[largest]);
            i = largest;
            l = 2*i + 1;
            r = 2*i + 2;
        } else {
            break;
        }
    }
}

// Função principal de HeapSort
void heapSort(char** arr, int n, int* index) {
    // Constrói o heap (rearranja o array)
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i, index);

    // Extrai um por um os elementos do heap
    for (int i = n-1; i >= 0; i--) {
        // Move a raiz atual para o fim do array
        swap(&arr[0], &arr[i]);

        // Chama a função heapify na subárvore reduzida
        heapify(arr, i, 0, index);
    }
}

int main() {
    int n, s, i;
    scanf("%d %d", &n, &s);

    // Lê a chave de ordenação
    char key[s+1];
    scanf("%s", key);

    // Cria um índice para a chave
    int index[256];
    for (int i = 0; i < s; i++)
        index[(int)key[i]] = i;

    // Lê as palavras
    char** words = (char**) malloc(n * sizeof(char*));
    for (int i = 0; i < n; i++) {
        words[i] = (char*) malloc((s+1) * sizeof(char));
        scanf("%s", words[i]);
    }

    //Procura por erros
    for (i = 0; i < n; i++) {
      if (strcspn(words[i], key) == strlen(words[i])) {
        printf("A palavra %s eh invalida", words[i]);
        return 0;
      }  
    }

    // Executa o HeapSort
    heapSort(words, n, index);

    // Imprime as palavras ordenadas
    for (int i = n-1; i >= 0; i--) {
        printf("%s ", words[i]);
        free(words[i]);
    }
    printf("\n");

    free(words);
    return 0;
}
