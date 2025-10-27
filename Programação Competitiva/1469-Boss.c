#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Enviar o numero do funcionario - 1 nessa funcao
void query (int num, int employees, int** adjMatrix, int ages[], int* youngest, int* visited) {
    if (visited[num]) return;
    visited[num] = 1;

    for (int i = 0; i < employees; i++) {
        if (adjMatrix[i][num]) {
            if (ages[i] < *youngest) *youngest = ages[i];
            query(i, employees, adjMatrix, ages, youngest, visited);
        }
    }
}

// Debug
void printMatrix (int** adjMatrix, int employees) {
    printf("\n");
    for (int i = 0; i < employees; i++) {
        for (int j = 0; j < employees; j++) {
            printf("%i ", adjMatrix[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

int main () {
    int employees, relations, instructions;

    while (scanf("%i %i %i", &employees, &relations, &instructions) != EOF) {

        // Matriz de adjacencia binária (1 se está ligado, 0 se não está)
        // Numero de funcionario comeca em 1, entao tenho que sempre chamar com -1
        // Fazer com alocacao dinamica facilita na hora da instrucao T
        int **adjMatrix;
        adjMatrix = malloc(employees * sizeof(int*));
        for (int i = 0; i < employees; i++) adjMatrix[i] = calloc(employees, sizeof(int));
        int ages[employees];

        for (int i = 0; i < employees; i++) scanf("%i", &ages[i]);

        int x, y;
        for (int i = 0; i < relations; i++) {
            scanf("%i %i", &x, &y);
            // Funcionario x gerencia o funcionario y diretamente
            adjMatrix[x-1][y-1] = 1;
        }

        char inst;
        for (int i = 0; i < instructions; i++) {
            int youngest = 999;
            scanf(" %c", &inst);
            switch (inst) {
                case 'T':
                    scanf("%i %i", &x, &y);
                    //printMatrix(adjMatrix, employees);

                    /*
                    Idade não se troca pois o funcionario 4 continua sendo o funcionario 4, entao a idade continua a mesma
                    Porem, suas adjacencias mudaram
                    */
                    /*
                    int auxAge = ages[x-1];
                    ages[x-1] = ages[y-1];
                    ages[y-1] = auxAge;
                    */

                    int* aux = adjMatrix[x-1];
                    adjMatrix[x-1] = adjMatrix[y-1];
                    adjMatrix[y-1] = aux;

                    for (int z = 0; z < employees; z++) {
                        int aux2;
                        aux2 = adjMatrix[z][x-1];
                        adjMatrix[z][x-1] = adjMatrix[z][y-1];
                        adjMatrix[z][y-1] = aux2;
                    }

                    //printMatrix(adjMatrix, employees);
                    break;
                case 'P':
                    scanf("%i", &x);
                    //printMatrix(adjMatrix, employees);
                    int visited[employees];
                    memset(visited, 0, sizeof(visited));
                    query(x-1, employees, adjMatrix, ages, &youngest, visited);
                    if (youngest == 999) printf("*\n");
                    else printf("%i\n", youngest);
                    break;
            }
        }
        for (int i = 0; i < employees; i++) {
            free(adjMatrix[i]);
        }
        free(adjMatrix);
    }
}