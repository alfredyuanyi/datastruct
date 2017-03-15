#include <stdio.h>
#include <stdlib.h>
#include "binaryheap.h"

#define MinPQSize (5)
// MinData 必须小于所有优先队列的值,需要预先设定好.
#define MinData (-1)

struct HeapStruct{
    int capacity;
    int size;
    ElementType *array;
};

PriorityQueue Initialize(int MaxElements){
    PriorityQueue h;
    if(MaxElements < MinPQSize){
        printf("MaxElements is too small!\n");
        exit(1);
    }
    h = malloc(sizeof(struct HeapStruct));
    if(h == NULL){
        printf("Out of space!\n");
        exit(1);
    }
    h->array = malloc(sizeof(ElementType) * (MaxElements + 1));
    if(h->array == NULL){
        printf("Out of space!\n");
        exit(1);
    }
    h->capacity = MaxElements;
    h->size = 0;
    h->array[0] = MinData;
    return h;
}

void Destroy(PriorityQueue h){
    if(h != NULL){
        free(h->array);
        free(h);
    }
}

void MakeEmpty(PriorityQueue h){
    if(h != NULL){
        int i;
        for(i = 1; i <= h->size; i++){
            h->array[i] = MinData;
        }
        h->size = 0;
    }
}

int IsEmpty(PriorityQueue h){
    if(h == NULL){
        printf("NULL PQ?\n");
        exit(1);
    }
    return h->size == 0;
}

int IsFull(PriorityQueue h){
    if(h == NULL){
        printf("NULL PQ?\n");
        exit(1);
    }
    return h->size == h->capacity;
}

void Insert(ElementType x, PriorityQueue h){
    int i;
    if(IsFull(h)){
        printf("PQ is full!\n");
        exit(1);
    }
    for(i = ++h->size; h->array[i / 2] > x; i = i / 2){
        h->array[i] = h->array[i / 2];
    }
    h->array[i] = x;
}

void Traverse(PriorityQueue h){
    if(h != NULL){
        int i;
        for(i = 1; i <= h->size; i++){
            printf("%d ", h->array[i]);
        }
        printf("\n");
    }
}

ElementType DeleteMin(PriorityQueue h){
    int i, smaller;
    ElementType minElement, lastElement;
    if(IsEmpty(h)){
        printf("Empty PQ!\n");
        exit(1);
    }
    minElement = h->array[1];
    lastElement = h->array[h->size--];
    for(i = 1; i * 2 <= h->size; i = smaller){
        if(i * 2 == h->size){
            if(h->array[i * 2] >= lastElement)
                break;
            else
                smaller = i * 2;
        }
        else
            smaller = h->array[i * 2] < h->array[i * 2 + 1]?(i * 2): (i * 2 + 1); 
        h->array[i] = h->array[smaller];
    }
    h->array[i] = lastElement;
    return minElement;
}

ElementType FindMin(PriorityQueue h){
    if(IsEmpty(h)){
        printf("Empty PQ!\n");
        exit(1);
    }
    return h->array[1]; 
}

void PercolateDown(PriorityQueue h, int NodeIndex){
    int i, smaller;
    ElementType temp;
    for(i = NodeIndex; i * 2 <= h->size; i = smaller){
        if(i * 2 != h->size){
            smaller = h->array[i * 2] < h->array[i * 2 + 1]? i * 2: i * 2 + 1;
        }
        else if(h->array[i * 2] < h->array[i]){
            smaller = i * 2;
        }
        else
            break;
        if(h->array[i] > h->array[smaller]){
            temp = h->array[i];
            h->array[i] = h->array[smaller];
            h->array[smaller] = temp;
        }
    }
}

PriorityQueue BuildHeap(ElementType *elements, int n){
    PriorityQueue h = Initialize(n);
    int i;
    for(i = 1; i <= n; i++)
        h->array[i] = elements[i - 1];
    h->size = n;
    for(i = n / 2; i > 0; i--)
        PercolateDown(h, i);
    return h;
}

int main(){
    ElementType elements[15] = {150, 80, 40, 30, 10, 70, 110, 100, 20, 90, 60, 50, 120, 140, 130};
    PriorityQueue h = BuildHeap(elements, 15);
    // MakeEmpty(h);
    // Insert(13, h);
    // Insert(21, h);
    // Insert(16, h);
    // Insert(24, h);
    // Insert(31, h);
    // Insert(19, h);
    // Insert(68, h);
    // Insert(65, h);
    // Insert(26, h);
    // Insert(32, h);
    // Insert(14, h);
    // Traverse(h);
    // ElementType element = DeleteMin(h);
    // printf("delete: %d\n", element);
    Traverse(h);
    printf("IsEmpty: %d\n", IsEmpty(h));
    printf("IsFull: %d\n", IsFull(h));
    Destroy(h);
    return 0;
}