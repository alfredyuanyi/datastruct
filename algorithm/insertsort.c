#include <stdio.h>
#include <stdlib.h>

typedef int ElementType;

#define M (1000)

void InsertSort(ElementType a[], int n){
    int i, j;
    ElementType temp;
    for(i = 1; i < n; i++){
        temp = a[i];
        for(j = i; j > 0 && a[j - 1] > temp; j--){
            a[j] = a[j - 1];
        }
        a[j] = temp;
    }
}

int main(){
    int i = 0;
    ElementType a[M];
    srand((unsigned)time(0));
    for(; i < M; i++){
        a[i] = rand() % (1000-0);
    }
    InsertSort(a, M);
    for(i = 0; i < M; i++)
        printf("%d | ", a[i]);
    printf("\n");
    return 0;
}