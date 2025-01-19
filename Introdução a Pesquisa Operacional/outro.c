#include <stdio.h> 
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>

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

// Função para calcular o limite superior (bound)
double calcular_limite(int nivel, double lucro, double peso, int capacidade) {
    if (peso > capacidade) return 0;

    double lucro_estimado = lucro;
    int capacidade_restante = capacidade - peso;

    // Adicionar itens de forma gulosa
    for (int i = nivel; i < nItems; i++) {
        if (itens[i].peso <= capacidade_restante) {
            capacidade_restante -= itens[i].peso;
            lucro_estimado += itens[i].lucro;
        } else {
            lucro_estimado += itens[i].lucro * (capacidade_restante / itens[i].peso);
            break;
        }
    }
    return lucro_estimado;
}

// Função para resolver o TTP usando Branch-and-Bound
int resolver_ttp(int capacidade, double *tempo_execucao) {
    clock_t inicio = clock();

    int melhor_lucro = 0;
    double peso_atual = 0;
    double lucro_atual = 0;
    int nivel_atual = 0;

    // Pilha para simular árvore de BnB
    typedef struct {
        int nivel;
        double lucro;
        double peso;
        double limite;
    } No;
    No pilha[1000];
    int topo = 0;

    // Adicionar nó raiz
    pilha[topo++] = (No){0, 0, 0, calcular_limite(0, 0, 0, capacidade)};

    while (topo > 0) {
        No no_atual = pilha[--topo];

        if (no_atual.limite <= melhor_lucro) continue;
        if (no_atual.nivel == nItems) {
            if (no_atual.lucro > melhor_lucro) melhor_lucro = no_atual.lucro;
            continue;
        }

        // Excluir item atual
        pilha[topo++] = (No){
            no_atual.nivel + 1,
            no_atual.lucro,
            no_atual.peso,
            calcular_limite(no_atual.nivel + 1, no_atual.lucro, no_atual.peso, capacidade)};

        // Incluir item atual
        item item_atual = itens[no_atual.nivel];
        if (no_atual.peso + item_atual.peso <= capacidade) {
            pilha[topo++] = (No){
                no_atual.nivel + 1,
                no_atual.lucro + item_atual.lucro,
                no_atual.peso + item_atual.peso,
                calcular_limite(no_atual.nivel + 1, no_atual.lucro + item_atual.lucro, no_atual.peso + item_atual.peso, capacidade)};
        }
    }

    clock_t fim = clock();
    *tempo_execucao = (double)(fim - inicio) / CLOCKS_PER_SEC;
    return melhor_lucro;
}

// Função para ler o arquivo de entrada
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

    fscanf(inst, "%*s %i\n", &nCid); // => read dimension
    fscanf(inst, "%*s %*s %*s %i\n", &nItems); // => read item number
    fscanf(inst, "%*s %*s %*s %d\n", &maxPeso); // => read max capacity
    fscanf(inst, "%*s %*s %d\n", &minVel); // => read min velocity
    fscanf(inst, "%*s %*s %d\n", &maxVel); // => read max velocity
    fscanf(inst, "%*s %*s %d\n", &rate); // => read rent rate

    fscanf(inst, "%*[^\n]\n"); // => skip edge weight type
    fscanf(inst, "%*[^\n]\n"); // => skip node coord header

    cidades = malloc(nCid * sizeof(cidade));
    itens = malloc(nItems * sizeof(item));

    // => read all city nodes
    for (int i = 0; i < nCid; i++){
        fscanf(inst, "%d %lf %lf\n", &cidades[i].index, &cidades[i].X, &cidades[i].Y);
        cidades[i].qte = 0;
    }

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

        fscanf(inst, "%d %lf %lf %d\n", &readItem.index, &readItem.lucro, &readItem.peso, &readItem.indCidade);

        readItem.indCidade -= 1;
        readItem.index -= 1;

        // => malloc|realloc to increase array size
        if (cidades[i].qte == 0) {
            cidades[i].itens = malloc(sizeof(item));
            cidades[i].qte++;
        }
        else {
            cidades[i].qte++;
            cidades[i].itens = realloc(cidades[i].itens, cidades[i].qte*sizeof(item));
        }

        cidades[i].itens[i] = readItem.index;
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

// Função principal
int main() {
    char arquivo[] = "instancia.ttp";
    read(arquivo);

    printf("| Instância | Cidades | Itens | Lucro Total (R$) | Tempo de Execução (s) |\n");
    printf("|-----------|---------|-------|------------------|------------------------|\n");

    double tempo_execucao;
    int lucro = resolver_ttp(maxPeso, &tempo_execucao);

    printf("| 1         | %d       | %i     | %.2f            | %.2f                   |\n", nCid, nItems, (double)lucro, tempo_execucao);

    return 0;
}