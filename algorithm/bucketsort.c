#include <stdio.h>
#include <stdlib.h>

#define N 10
#define M 1000

int main(){
    int count[M] = {0};
    int a, i;
    for(i = 1; i <= N; i++){
        scanf("%d", &a);
        count[a] = 1;
    }
    for(i = 0; i < M; i++){
        if(count[i] != 0) printf("%d ", i);
    }
    return 0;
    
}