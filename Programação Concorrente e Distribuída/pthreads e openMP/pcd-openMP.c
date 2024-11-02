#include <stdio.h>
#include <omp.h>
#define N 1000000000

int main(int argc, char *argv[]){
  double x, final;
  int i;

  final = 1;
  x = 1 + 1.0/N;

  #pragma omp parallel default(none) private(i) shared(x) reduction(*:final)
  {
#pragma omp for
    for(i=0; i<N; i++) {
      final = final*x;
    }
  }
  
  printf("Resultado=%lf\n",final);
  return 0;
}  