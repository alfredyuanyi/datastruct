#include <stdio.h>
#include <stdlib.h>
#include <time.h>


typedef int ElementType;

#define M (1000)

void Swap(ElementType *a, ElementType *b){
    ElementType temp = *a;
    *a = *b;
    *b = temp;
}

ElementType GetPivot(ElementType a[], int left, int right){
    int center = (left + right) / 2;
    if(a[left] > a[center])
        Swap(&a[left], &a[center]);
    if(a[left] > a[right])
        Swap(&a[left], &a[right]);
    if(a[center] > a[right])
        Swap(&a[center], &a[right]);
    Swap(&a[center], &a[right - 1]);
    return a[right -1];
}

void Qsort(ElementType a[], int left, int right){
    int i, j;
    ElementType pivot;
    if(right - left <= 1){
        if(a[left] > a[right])
            Swap(&a[left], &a[right]);
            return;
    }
    else{
        pivot = GetPivot(a, left, right);
        i = left;
        j = right - 1;
        for(;;){
            while(a[++i] < pivot) {}
            while(a[--j] > pivot) {}
            if(i < j)
                Swap(&a[i], &a[j]);
            else
                break;
        }
        Swap(&a[i], &a[right -1]);
        Qsort(a, left, i - 1);
        Qsort(a, i + 1, right);
    }
}

void QuickSort(ElementType a[], int n){
    Qsort(a, 0, n -1);
}


int main(){
    int i = 0;
    ElementType a[M];
    srand((unsigned)time(0));
    for(; i < M; i++){
        a[i] = rand() % (1000-0);
    }
    QuickSort(a, M);
    for(i = 0; i < M; i++)
        printf("%d | ", a[i]);
    printf("\n");
    return 0;
}