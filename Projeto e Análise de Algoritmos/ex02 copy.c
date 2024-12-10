#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <float.h>

typedef struct {
    double x, y;
} ponto;

// => Comp em termos de X para usar no QS da stdlib
int compXQS(const void* a, const void* b) {
    ponto* p1 = (ponto*)a;
    ponto* p2 = (ponto*)b;
    return (p1->x - p2->x);
}

// => Idem para Y
int compYQS(const void* a, const void* b) {
    ponto* p1 = (ponto*)a;
    ponto* p2 = (ponto*)b;
    return (p1->y - p2->y);
}

// => Formula da distancia
double dist(ponto p1, ponto p2) {
    return sqrt(pow(p1.x - p2.x, 2) + pow(p1.y - p2.y, 2));
}

// => condicao de parada, testar na marra para problemas pequenos
double condParada(ponto pontos[], int n) {
    // maior valor possivel de double, nao sei quais valores o professor usa
    double menor = 99999999999.0;
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (dist(pontos[i], pontos[j]) < menor) {
                menor = dist(pontos[i], pontos[j]);
            }
        }
    }
}

// => Olhar no caderno
// => divConq testou esquerda e direita, agora juntaMetades testa o meio delas, a faixa do meio
// => Tambem testa a distancia vertical
double juntaMetades(ponto faixa[], int size, double d) {
    double min = d;
    qsort(faixa, size, sizeof(ponto), compYQS);
    for (int i = 0; i < size; i++) {
        for (int j = i + 1; j < size && (faixa[j].y - faixa[i].y) < min; j++) {
            if (dist(faixa[i], faixa[j]) < min) {
                min = dist(faixa[i], faixa[j]);
            }
        }
    }
    return min;
}

// => Divisao e conquista
double divConq(ponto pontos[], int n) {

    // cond de parada
    if (n <= 3) return condParada(pontos, n);

    int mid = n / 2;
    ponto midponto = pontos[mid];

    double esq = divConq(pontos, mid);
    double dir = divConq(pontos + mid, n - mid);
    double menorD;

    if (esq <= dir) menorD = esq;
    else menorD = dir;

    ponto faixa[n];
    int j = 0;
    for (int i = 0; i < n; i++) {
        double distaux = pontos[i].x - midponto.x;
        if (distaux < 0) distaux *= -1.0;
        if (distaux < menorD) {
            faixa[j] = pontos[i];
            j++;
        }
    }

    double aux = juntaMetades(faixa, j, menorD);
    if (menorD <= aux) return menorD;
    else return aux;
}

// Ordena e já envia para a proxima funcao
double sort(ponto pontos[], int n) {
    qsort(pontos, n, sizeof(ponto), compXQS);
    return divConq(pontos, n);
}

int main() {
    int n;
    scanf("%d", &n);
    ponto pontos[n];
    for (int i = 0; i < n; i++) {
        scanf("%lf %lf", &pontos[i].x, &pontos[i].y);
    }
    // 10 de precisao, nao 6
    printf("%.10f\n", sort(pontos, n));
    return 0;
}

// Resolucao obvia nao funciona, n^2 ou fatorial
// Distancias por "quadradinhos": ver a distancia de x e de y, em questao dos quadradinhos do plano
// Mais perto em quadradinhos deve ser mais perto na equacao
// Ordenar
// qsort() => stdlib.h
// Como usar: criar funcao que compare os pontos com (const void* a, const void* b) (criar pra x e y)
// Tem que passar: (ponteiro para o primeiro elemento, n de elementos, sizeof de cada elemento, funcao que ele vai usar para comparar e ordenar com base nela)
// 2T(n/2) + O(n) => O(n log n)