#include <stdio.h>
#include <math.h>

int bhaskara (float, float, float, float *, float *);

int main (void) {
  float A, B, C, x1, x2;
  int nraizes;

  printf("Vamos achar as raízes de uma equação do segundo grau!\n");
  printf("Lembrando seu formato: Ax^2 + Bx + C\n");
  printf("Digite o valor de A: ");
  scanf("%f", &A);
  printf("Digite o valor de B: ");
  scanf("%f", &B);
  printf("Digite o valor de C: ");
  scanf("%f", &C);

  nraizes = bhaskara (A, B, C, &x1, &x2);
  
  if (nraizes == 0) 
    printf("Não existem raízes reais\n");
  else if (nraizes == 1)
    printf("A raíz única é %.2f\n", x1);
  else
    printf("As raízes são %.2f e %.2f\n", x1, x2);
}

int bhaskara (float A, float B, float C, float *x1, float *x2) {
  float delta;

  delta = (B * B) - 4 * A * C;

  if (delta < 0)
    return 0;
  else if (delta == 0) {
    *x1 = -B / (2 * A);
    return 1;
  }
  else {
    *x1 = (-B + sqrtf(delta)) / (2 * A);
    *x2 = (-B - sqrtf(delta)) / (2 * A);
    return 2;
  }
}















//Provavelmente vamos ter de usar ifs para poder detectar se temos ou não respostas