#include <stdio.h>
#include <stdlib.h>
#include "leftistheap.h"

/* 所有的操作,时间复杂度为O(logN)*/

struct TreeNode{
    ElementType element;
    PriorityQueue left;
    PriorityQueue right;
    /* 节点的零路径长(null path length) */
    int Npl;
};


PriorityQueue Initialize(void){
    return NULL;
}

int IsEmpty(PriorityQueue h){
    return h == NULL;
}

ElementType FindMin(PriorityQueue h){
    if(IsEmpty(h)){
        printf("Empty priorityqueue!\n");
        exit(1);
    }
    return h->element;
}

PriorityQueue Insert1(ElementType x, PriorityQueue h){
    PriorityQueue singleNode = malloc(sizeof(struct TreeNode));
    if(singleNode == NULL){
        printf("Out of space!\n");
        exit(1);
    }
    singleNode->element = x;
    singleNode->Npl = 0;
    singleNode->left = singleNode->right = NULL;
    h = Merge(h, singleNode);
    return h;
}

PriorityQueue DeleteMin(PriorityQueue h){
    PriorityQueue leftheap, rightheap;
    if(IsEmpty(h)){
        printf("Empty priorityqueue!\n");
        exit(1);
    }
    leftheap = h->left;
    rightheap = h->right;
    return Merge(leftheap, rightheap);
}

void Traverse(int depth, PriorityQueue h){
    int i;
    for(i = 0; i < depth; i++)
        printf("    ");
    if(h) 
	{     
        printf("%d\n", h->element);
        Traverse(depth + 1, h->left); 
		 // Attention: there's difference between traversing binary tree and common tree.
        Traverse(depth + 1, h->right);
    }
    else 
        printf("NULL\n");
}

void SwapChildren(PriorityQueue h){
    PriorityQueue temp = h->right;
    h->right = h->left;
    h->left = temp;
}

PriorityQueue Merge(PriorityQueue h1, PriorityQueue h2){
    if(h1 == NULL)
        return h2;
    else if(h2 == NULL)
        return h1;
    else if(h1->element > h2->element){
        h2->right = Merge(h1, h2->right);
        if(h2->left == NULL){
            h2->left = h2->right;
            h2->right = NULL;
        }
        else if(h2->left->Npl < h2->right->Npl)
            SwapChildren(h2);
        if(h2->right == NULL)
            h2->Npl = 0;
        else
            h2->Npl = h2->right->Npl + 1;
        return h2;
    }
    else{
        h1->right = Merge(h2, h1->right);
        if(h1->left == NULL){
            h1->left = h1->right;
            h1->right = NULL;
        }
        else if(h1->left->Npl < h1->right->Npl)
            SwapChildren(h1);
        if(h1->right == NULL)
            h1->Npl = 0;
        else
            h1->Npl = h1->right->Npl + 1;
        return h1;
    }
}



int main(){
    PriorityQueue h1 = Initialize();
    PriorityQueue h2 = Initialize();    
    int data[] =  {21, 10, 23, 14, 3, 26, 17, 8};    
    int data2[] = {18, 12, 33, 24, 6, 37, 7, 18};    
    int i;
    for(i=0; i<8; i++)
    {
        h1 = Insert(data[i], h1);
    }
    printf("\n=== after the leftist heap h1 is merged===\n");
    Traverse(1, h1);

    for(i=0; i<8; i++)
    {
        h2 = Insert(data2[i], h2);
    }
    printf("\n=== after the leftist heap h2 is merged===\n");
    Traverse(1, h2);
     
    h1 = Merge(h1, h2);
    printf("\n=== after both h1 and h2 are merged===\n");
    Traverse(1, h1);

    h1 = DeleteMin(h1);
    printf("\n=== after executing deleteMin operation ===\n");
    Traverse(1, h1);
    return 0;
}