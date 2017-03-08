#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef int ElementType;

#define M (100)

void Merge(ElementType a[], ElementType tempArray[], int left, int center, int right){
    int i = left, j = center + 1, k = left;
    while(i <= center && j <= right){
        if(a[i] <= a[j])
            tempArray[k++] = a[i++];
        else
            tempArray[k++] = a[j++];
    }
    while(i <= center)
        tempArray[k++] = a[i++];
    while(j <= right)
        tempArray[k++] = a[j++];
    for(i = left; i <= k - 1; i++)
        a[i] = tempArray[i];
}

void Msort(ElementType a[], ElementType tempArray[], int left, int right){
    int center;
    if(left < right){
        center = (left + right) / 2;
        Msort(a, tempArray, left, center);
        Msort(a, tempArray, center + 1, right);
        Merge(a, tempArray, left, center, right);
    }
}



void MergeSort(ElementType a[], int N){
    ElementType *tempArray;
    tempArray = malloc(sizeof(ElementType) * N);
    if(tempArray == NULL){
        printf("Out of space!");
        exit(1);
    }
    Msort(a, tempArray, 0, N - 1);
    free(tempArray);
}

int main(){
    int i = 0;
    ElementType a[M];
    srand((unsigned)time(0));
    for(; i < M; i++){
        a[i] = rand() % (100-0);
    }
    printf("before:\n");
    for(i = 0; i < M; i++)
        printf("%d | ", a[i]);
    printf("\n");
    MergeSort(a, M);
    for(i = 0; i < M; i++)
        printf("%d | ", a[i]);
    printf("\n");
    return 0;
}