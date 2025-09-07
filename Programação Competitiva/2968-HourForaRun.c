#include <stdio.h>
#include <math.h>
 
int main() {
 
    int laps, signs;
    float total;
    
    scanf("%i", &laps);
    scanf("%i", &signs);
    total = laps * signs;
    
    for (int i = 1; i <=8; i++){
        printf("%.0f ", ceil(total*((float)i/10)));
    }
    printf("%.0f\n", ceil(total*0.9));
    
    
    return 0;
}