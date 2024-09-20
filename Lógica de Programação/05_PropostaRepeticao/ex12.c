#include <stdio.h>

int main (void) {
  int num, i;
  printf("Digite qual tabuada você gostaria de ver: ");
  scanf("%i", &num);
  for (i = 1; i <= 10; i++) {
    printf("%i x %i = %i\n", num, i, num * i);
  }
}