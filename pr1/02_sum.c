#include <stdio.h>

int main(){
    double a, b, sum;
    if(scanf("%lf %lf", &a, &b) == 2){
        sum = a + b;
        printf("%lf\n", sum);
    }
    
    return 0;
}
