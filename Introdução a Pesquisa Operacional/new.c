#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

struct item {
    int index;
    double lucro;
    double peso;
    int indCidade;
} typedef item;

struct cidade {
    int index;
    int *itens;
    int qte;
    double X;
    double Y;
} typedef cidade;

cidade *cidades;
item *itens;
int nCid;
int nItems;
double rate;
double minVel;
double maxVel;
double maxPeso;
double maxLucro;
double bestPW;
double averagePW;
double medianPW;
double **dist;

void saveTSP() {
    printf("cheguei");
    FILE *tsp = fopen("tspdata", "w");
    fprintf(tsp, "set N := ");
    for (int i = 1; i <= nCid; i++) {
        fprintf(tsp, "%i ", i);
    }
}

void read(char *fileName) {
    char name[200] = "./Inst/";
    strcat(name, fileName);

    FILE *inst = fopen(name, "r");
    if (inst == NULL) {
        printf("Erro\n");
        return;
    }

    fscanf(inst, "%*[^\n]\n"); // => skip name
    fscanf(inst, "%*[^\n]\n"); // => skip type

    fscanf(inst, "%*s %i", &nCid); // => read dimension
    fscanf(inst, "%*s %*s %*s %i", &nItems); // => read item number
    fscanf(inst, "%*s %*s %*s %i", &maxPeso); // => read max capacity
    fscanf(inst, "%*s %*s %i", &minVel); // => read min velocity
    fscanf(inst, "%*s %*s %i", &maxVel); // => read max velocity
    fscanf(inst, "%*s %*s %i", &rate); // => read rent rate

    fscanf(inst, "%*[^\n]\n"); // => skip edge weight type
    fscanf(inst, "%*[^\n]\n"); // => skip node coord header

    printf("Consegue\n");

    cidades = malloc(nCid * sizeof(cidade));
    itens = malloc(nItems * sizeof(item));

    // => read all city nodes
    for (int i = 0; i < nCid; i++){
        fscanf(inst, "%d %lf %lf", &cidades[i].index, &cidades[i].X, &cidades[i].Y);
        cidades[i].qte = 0;
    }

    printf("Consegue\n");

    fscanf(inst, "%*[^\n]\n"); // => skip item header

    maxLucro = 0;
    bestPW = -1;
    averagePW = 0;
    // => profit array because you can only get 1 item in each city, so you should only add 1 max profit item per city to maxLucro
    double *cidMaxLucro = malloc(nCid*sizeof(double));
    memset(cidMaxLucro, -1, nCid*sizeof(double));
    double *itemPW = malloc(nItems*sizeof(double));
    for (int i = 0; i < nItems; i++) {
        item readItem;

        fscanf(inst, "%d %lf %lf %d", &readItem.index, &readItem.lucro, &readItem.peso, &readItem.indCidade);
        printf("Consegue\n");
        readItem.indCidade -= 1;
        readItem.index -= 1;

        // => malloc|realloc to increase array size
        if (cidades[readItem.indCidade].qte == 0) {
            cidades[readItem.indCidade].itens = malloc(sizeof(int));
            cidades[readItem.indCidade].qte++;
        }
        else {
            cidades[readItem.indCidade].qte++;
            cidades[readItem.indCidade].itens = realloc(cidades[readItem.indCidade].itens, cidades[readItem.indCidade].qte*sizeof(int));
        }

        cidades[readItem.indCidade].itens[cidades[readItem.indCidade].qte - 1] = readItem.index;
        itens[i] = readItem;

        // => check if another item on the same city has a bigger profit than this one
        if (cidMaxLucro[readItem.indCidade] < readItem.lucro) cidMaxLucro[readItem.indCidade] = readItem.lucro;
        
        if (readItem.lucro/readItem.peso > bestPW) bestPW = readItem.lucro/readItem.peso;
        averagePW += readItem.lucro/readItem.peso;
        itemPW[i] = readItem.lucro/readItem.peso;
    }
    
    for (int i = 1; i < nCid; i++) maxLucro += cidMaxLucro[i];
    // => file is not used anywhere after this point, so we close it here.
    fclose(inst);

    // Save data
    saveTSP();

    averagePW /= nItems;

    // => Bubblesort to sort the vector. Quadratic, but works and it was simple to code.
    for (int i = nItems; i > 0; i--) {
        for (int j = 1; j < i; j++) {
            if (itemPW[j-1] > itemPW[j]) {
                double aux = itemPW[j-1];
                itemPW[j-1] = itemPW[j];
                itemPW[j] = aux;
            }
        }
    }

    if (nItems % 2 == 0) medianPW = (itemPW[(nItems/2) - 1] + itemPW[nItems/2]) / 2.0;
    else medianPW = itemPW[nItems/2];

    // => malloc for the dist matriz
    dist = malloc(nCid * sizeof(double*));
    for (int i = 0; i < nCid; i++) dist[i] = malloc(nCid * sizeof(double));

    // => processing distances
    for (int i = 0; i < nCid; i++) {
        for (int j = i; j < nCid; j++) {
            if (i == j) dist[i][j] = 0.0;
            else {
                // => better to use pow()
                dist[i][j] = ceil(sqrt(pow(cidades[j].X - cidades[i].X, 2) + pow(cidades[j].Y - cidades[i].Y, 2)));
                dist[j][i] = dist[i][j];
            }
        }
    }
}

int main(void) {
    read("instancia.ttp");
}
