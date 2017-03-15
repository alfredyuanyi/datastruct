//选择问题,输入N个元素以及一个整数k,N个元素的集可以是全序的,找出第k小个元素.
#include <stdio.h>
#include <stdlib.h>
typedef int ElementType;
typedef struct HeapStruct *PriorityQueue;

#define M (10)

/*方法一: 
将前k个元素存入数组并排序,将最大的元素放在第k个位置上,再依次将后面的N-k个元素同数组中的第k个元素比较,若该元素较小则将数组中的第k个
丢弃,并将该元素插入到数组中的正确位置中.
时间复杂度:O(N * k)
*/
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

ElementType ChooseKBySort(ElementType a[], int n, int k){
    int i, j;
    ElementType temp;
    InsertSort(a,k);
    for(i = k; i < n; i++){
        temp = a[i];
        for(j = k; j > 0 && a[j - 1] > temp; j--){
            a[j] = a[j - 1];
        }
        a[j] = temp;
    }
    return a[k - 1];
}

/* 方法二:
将所有元素存入数组,对该数组应用heap中的BuildHeap算法,最后执行k次DeleteMin操作,则从该堆中最后提取出来的元素就是答案
时间复杂度: O(N + k*logN)
*/

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

ElementType ChooseKByHeap(ElementType *a, int n, int k){
    PriorityQueue h = BuildHeap(a, n);
    Traverse(h);
    int i;
    for(i = 0; i < k - 1; i++)
        printf("delete : %d\n", DeleteMin(h));
    return FindMin(h);
}


int main(){
    int i = 0, k = 5;
    ElementType a[M];
    srand((unsigned)time(0));
    for(; i < M; i++){
        a[i] = rand() % (10-0);
        printf("%d ", a[i]);
    }
    printf("\n");
    PriorityQueue h = BuildHeap(a, M);
    printf("index: %d, value: %d\n", k, ChooseKByHeap(a, M, k));
    // int j = ChooseKBySort(a, M, k);
    // printf("index: %d, value: %d\n", k, j);
    // InsertSort(a, M);
    // for(i = 0; i < M; i++)
    //     printf("%d | ", a[i]);
    // printf("\n");
    return 0;
}