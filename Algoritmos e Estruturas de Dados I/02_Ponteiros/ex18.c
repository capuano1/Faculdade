#include <stdio.h>
#include <math.h>

void esfera (float, float *, float *);

int main (void) {
  float r, ar, vol;
  printf("Insira o raio da esfera: ");
  scanf("%f", &r);
  esfera (r, &ar, &vol);
  printf("Área: %.2f\nVolume: %.2f\n", ar, vol);
}

void esfera (float raio, float *area, float *volume) {
  *area = 4 * M_PI * (raio * raio);
  *volume = (4.0/3.0) * M_PI * (raio * raio * raio);
}