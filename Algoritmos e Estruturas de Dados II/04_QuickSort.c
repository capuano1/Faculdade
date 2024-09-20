#include <stdio.h>
#include <stdlib.h>

/*Todos os códigos que estão apenas comentados serviram para testar o código e resolver
os problemas que apareciam na hora de arranjar da maneira correta o array, assim como a
função imprimeLista*/

void swap (int* x, int* y) {
  int temp = *x;
  *x = *y;
  *y = temp;
}

void imprimeLista (int* v, int n) {
  int i;
  for (i=0; i<n; i++)
    printf("%i ", v[i]);
  printf("\n");
}

int part (int* v, int strt, int end, int indpivot) {
  int pivot = v[indpivot];
  int pInd = strt;
  int i;

  for (i=strt; i<=end; i++) {
    if (v[i] <= pivot && i != indpivot) {
      //printf("B: ");
      //imprimeLista(v, 5);
      swap(&v[pInd], &v[i]);
      //printf("D: ");
      //imprimeLista(v, 5);
      //printf("\n");
      pInd++;
    }
  }
  swap (&v[pInd], &v[indpivot]);
  //printf("%i %i %i %i\n", pInd, strt, end, indpivot);
  return pInd;
}

void quicksort (int* v, int strt, int end, int alt, int* max, int* min) {
  int pivot;
  pivot = end;
  
  if (strt < end) {
    int p = part(v, strt, end, pivot);
    quicksort(v, strt, p-1, alt+1, max, min);
    quicksort(v, p+1, end, alt+1, max, min);
  }
  else {
    if (alt < *min)
      *min = alt;
    if (alt > *max)
      *max = alt;
    return;
  }
}

int partmed (int* v, int strt, int end, int indpivot) {
  int pivot = v[indpivot];
  int pInd = strt;
  int i;

  for (i=strt; i<=end; i++) {
    if (v[i] <= pivot && i != indpivot) {
      //printf("B: ");
      //imprimeLista(v, 10);
      swap(&v[pInd], &v[i]);
      //printf("D: ");
      //imprimeLista(v, 10);
      //printf("\n");
      if (pInd == indpivot)
        indpivot = i;
      pInd++;
    }
  }
  swap (&v[pInd], &v[indpivot]);
  //printf("%i %i %i %i %i\n", pInd, strt, end, indpivot, pivot);
  return pInd;
}

void quicksortmed (int* v, int strt, int end, int alt, int* max, int* min) {
  int pivot, med;
  med = (strt + end)/2;

  if(v[strt] < v[med]) {
    if (v[med] < v[end])
      pivot = med;
    else {
      if (v[strt] < v[end])
        pivot = end;
      else
        pivot = strt;
    }
  }
  else {
    if (v[end] < v[med])
      pivot = med;
    else {
      if (v[end] < v[strt])
        pivot = end;
      else
        pivot = strt;
    }
  }
  if (strt < end) {
    int p = partmed(v, strt, end, pivot);
    quicksortmed(v, strt, p-1, alt+1, max, min);
    quicksortmed(v, p+1, end, alt+1, max, min);
  }
  else {
    if (alt < *min)
      *min = alt;
    if (alt > *max)
      *max = alt;
    return;
  }
}

int main(void) {
  int i, n, *v, *v2, *min, *max;
  int fim;
  
  min = malloc(sizeof(int));
  max = malloc(sizeof(int));
  scanf("%i", &n);
  v = malloc(n*sizeof(int));
  v2 = malloc(n*sizeof(int));
  for (i=0; i<n; i++) {
    scanf("%i", &v[i]);
    v2[i] = v[i];
  }
  //printf("Unsorted v:\n");
  //imprimeLista(v, n);
  *min = 2147483647;
  *max = 0;
  quicksort(v, 0, n-1, 0, max, min);
  if (*max >= *min)
    fim = *max - *min;
  else
    fim = *min - *max;
  printf("%i\n", fim);
  //imprimeLista(v, n);
  //printf("Unsorted v2:\n");
  //imprimeLista(v2, n);
  *min = 2147483647;
  *max = 0;
  quicksortmed(v2, 0, n-1, 0, max, min);
  if (*max >= *min)
    fim = *max - *min;
  else
    fim = *min - *max;
  printf("%i", fim);
  //imprimeLista(v2, n);

  
  return 0;
}