#include <stdio.h>
#include <omp.h>
#include <time.h>

int main(int argc, char *argv[]){
  double x, final;
  unsigned long long int i;
  unsigned long long int N = 10000000000;
  clock_t start;
  clock_t parallel;

  start = clock();

  final = 1;
  x = 1 + 1.0/N;

  parallel = clock();
  #pragma omp parallel default(none) private(i) shared(x, N) reduction(*:final) num_threads(16)
  {
  #pragma omp for
    for(i=0; i<N; i++) {
      final = final*x;
    }
  }
  float paralleltime = ((double)clock() - parallel) / CLOCKS_PER_SEC;
  

  printf("Resultado=%lf\n",final);
  float totaltime = ((double)clock() - start) / CLOCKS_PER_SEC;
  printf("Time: %f\n", totaltime);
  printf("Parallel: %f\n", paralleltime);
  printf("Parallel Time: %f\n", paralleltime/totaltime);
  return 0;
}  