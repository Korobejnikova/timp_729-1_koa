#include <stdio.h>

int main(){
    long int n, x, i, count = 0;;
    if(scanf("%ld", &n) == 1){
        for(i = 1; i <= n; i++){
            if(scanf("%ld", &x) == 1){
                if(x < 0){
                    ++count;
                }
            }
        }
        printf("%ld", count);
    }
    return 0;
}
