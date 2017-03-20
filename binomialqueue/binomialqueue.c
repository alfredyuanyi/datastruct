#include <stdio.h>
#include <stdlib.h>

#include "binomialqueue.h"

#define MaxTrees (14)
#define Capacity (16383)
#define Infinity (30000L)

struct BinNode{
    ElementType element;
    Position leftChild;
    Position nextSibling;
};

struct Collection{
    int currentSize;
    BinTree theTrees[MaxTrees];
};

BinQueue Initialize(void){
    BinQueue h;
    int i;
    h = malloc(sizeof(struct Collection));
    if(h == NULL){
        printf("Out of space!\n");
        exit(1);
    }
    for(i = 0; i < MaxTrees; i++)
        h->theTrees[i] = NULL;
    h->currentSize = 0;
    return h;
}

int IsEmpty(BinQueue h){
    return h->currentSize == 0;
}

BinTree CombineTrees(BinTree t1, BinTree t2){
    if(t1->element > t2->element)
        return CombineTrees(t2, t1);
    t2->nextSibling = t1->leftChild;
    t1->leftChild = t2;
    return t1;
}

BinQueue Merge(BinQueue h1, BinQueue h2){
    BinTree t1, t2, carry = NULL;
    int i, j;
    if(h1->currentSize + h2->currentSize > Capacity){
        printf("Merge would exceed capacity!\n");
        exit(1);
    }
    h1->currentSize += h2->currentSize;
    for(i = 0, j = 1; j <= h1->currentSize; i++, j *= 2){
        t1 = h1->theTrees[i]; t2 = h2->theTrees[i];
        // !!是为了把非0值转换为1.
        switch(!!t1 + 2 * !!t2 + 4 * !!carry){
            case 0:
            case 1:
                break;
            case 2:
                h1->theTrees[i] = t2;
                h2->theTrees[i] = NULL;
                break;
            case 4:
                h1->theTrees[i] = carry;
                carry = NULL;
                break;
            case 3:
                carry = CombineTrees(t1, t2);
                h1->theTrees[i] = h2->theTrees[i] = NULL;
                break;
            case 5:
                carry = CombineTrees(t1, carry);
                h1->theTrees[i] = NULL;
                break;
            case 6:
                carry = CombineTrees(t2, carry);
                h2->theTrees[i] = NULL;
                break;
            case 7:
                h1->theTrees[i] = carry;
                carry = CombineTrees(t1, t2);
                h2->theTrees[i] = NULL;
                break;
        }
    }
    return h1;
}   

BinQueue Insert(ElementType x, BinQueue h){
    BinQueue temp;
    BinTree node;
    temp = Initialize();
    node = malloc(sizeof(struct BinNode));
    if(node == NULL){
        printf("Out of space\n");
        exit(1);
    }
    node->element = x;
    node->leftChild = node->nextSibling = NULL;
    temp->theTrees[0] = node;
    temp->currentSize = 1;
    return Merge(h, temp);
}

ElementType DeleteMin(BinQueue h){
    int i, j;
    int minTree;
    BinQueue deletedQueue;
    Position deletedTree, oldRoot;
    ElementType minItem;
    if(IsEmpty(h)){
        printf("Empty Binomial queue!\n");
        exit(1);
    }
    minItem = Infinity;
    for(i = 0; i < MaxTrees; i++){
        if(h->theTrees[i] && h->theTrees[i]->element < minItem){
            minTree = i;
            minItem = h->theTrees[i]->element;
        }
    }
    deletedTree = h->theTrees[minTree];
    oldRoot = deletedTree;
    deletedTree = oldRoot->leftChild;
    free(oldRoot);
    deletedQueue = Initialize();
    deletedQueue->currentSize = (1 << minTree) - 1;
    for(j = minTree - 1; j >= 0; j--){
        deletedQueue->theTrees[j] = deletedTree;
        deletedTree = deletedTree->nextSibling;
        deletedQueue->theTrees[j]->nextSibling = NULL;
    } 
    h->theTrees[minTree] = NULL;
    h->currentSize -=deletedQueue->currentSize - 1;
    Merge(h, deletedQueue);
    return minItem;
}

ElementType FindMin(BinQueue h){
    int i;
    ElementType minItem = Infinity;
    for(i = 0; i < MaxTrees; i++){
        if(h->theTrees[i] && minItem > h->theTrees[i]->element)
            minItem = h->theTrees[i]->element;
    }
    return minItem;
}


int main(){
    BinQueue h = Initialize();
    h = Insert(1, h);
    h = Insert(2, h);
    h = Insert(3, h);
    h = Insert(4, h);
    h = Insert(5, h);
    h = Insert(6, h);
    h = Insert(7, h);
    printf("%d\n", DeleteMin(h));
    printf("%d\n", FindMin(h));
    return 0;
}