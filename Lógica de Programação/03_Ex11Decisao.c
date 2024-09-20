#include <stdio.h>

void resposta (float sal) {
  float percent, aument, finalS;
  if (sal <= 280.00) {
    percent = 20.00;
    aument = (percent / 100) * sal;
    finalS = aument + sal;
  }
  else if (sal > 280.00 && sal < 700.00) {
    percent = 15.00;
    aument = (percent / 100) * sal;
    finalS = aument + sal;
  }
  else if (sal >= 700.00 && sal < 1500.00) {
    percent = 10.00;
    aument = (percent / 100) * sal;
    finalS = aument + sal;
  }
  else {
    percent = 5.00;
    aument = (percent / 100) * sal;
    finalS = aument + sal;
  }
  printf("O salário de R$%.2f receberá um aumento em porcentagem de %.2f ou R$%.2f, totalizando um novo salário de R$%.2f", sal, percent, aument, finalS);
}

int main(void) {
  float sal;
  scanf("%f", &sal);
  resposta(sal);
  return 0;
}