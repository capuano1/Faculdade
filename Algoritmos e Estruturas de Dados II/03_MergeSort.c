#include <stdio.h>
#include <stdlib.h>

struct node {
  int dado;
  struct node* prox;
};

struct node* insere (struct node* first, int dado) {
  struct node* novo = malloc(sizeof(struct node));
  novo->dado = dado;
  novo->prox = first;
  return novo;
}

void separa (struct node* nums, struct node* a, struct node* b, int n) {
  int i,met = (n+1)/2;
  struct node* headrefa = a;
  struct node* headrefb = b;
  
  for (i=0; i < met; i++) {
    a = nums;
    a = a->prox;
    nums = nums->prox;
  }
  a->prox = NULL;
  a = headrefa;
  do {
    b = nums;
    b = b->prox;
    nums = nums->prox;
  }
  while (b != NULL);
  b = headrefb;
}

struct node* SortMerge (struct node* a, struct node* b) {
  struct node* final = NULL;

  if (a == NULL)
    return b;
  else if (b == NULL)
    return a;

  if (a->dado <= b->dado) {
    final = a;
    final->prox = SortMerge(a->prox, b);
  }
  else {
    final = b;
    final->prox = SortMerge(a, b->prox);
  }
  return final;
}

struct node* MergeSort (struct node* nums, int count) {
  int maxNum;
  struct node* a, *b;

  if (nums == NULL || nums->prox == NULL)
    return nums;

  separa(nums, a, b, count);
  MergeSort(a, (count+1)/2);
  MergeSort(b, count-((count+1)/2));
  nums = SortMerge(a, b);
  return nums;
}


int main(void) {
  int n, i, temp, count = 0;
  struct node* nums = NULL;
  struct node* headref;

  scanf("%i", &n);
  for (i=0; i < n; i++) {
    scanf("%i", &temp);
    nums = insere(nums, temp);
  }
  
  nums = MergeSort(nums, n);
  headref = nums;
  printf("%i", nums->dado);
  nums = nums->prox;
  while (nums != NULL) {
    printf(" %i", nums->dado);
    nums = nums->prox;
  }
  
  return 0;
}