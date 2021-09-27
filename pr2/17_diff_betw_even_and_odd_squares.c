#include <stdio.h>
#include <math.h>

int main(){
    long int n, x, i, sum = 0;;
    if(scanf("%ld", &n) == 1){
        for(i = 1; i <= n; i++){
            if(scanf("%ld", &x) == 1){
                sum += pow((double)-1, (double)i) * x * x;
            }
        }
        printf("%ld", sum);
    }
    return 0;
}
