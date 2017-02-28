#include <stdio.h>
#include <stdlib.h>

#include "binarysearchtree.h"

struct TreeNode{
    ElementType element;
    SearchTree left;
    SearchTree right;
};

SearchTree MakeEmpty(SearchTree t){
    if(t != NULL){
        MakeEmpty(t->left);
        MakeEmpty(t->right);
        free(t);
    }
    return NULL;
}

Position Find(ElementType x, SearchTree t){
    if(t == NULL)
        return NULL;
    if(t->element > x)
        return Find(x, t->left);
    else if(t->element < x)
        return Find(x, t->right);
    else
        return t;
}

Position FindMax(SearchTree t){
    if(t == NULL)
        return NULL;
    else if(t->right != NULL)
        return FindMax(t->right);
    else
        return t;
}

Position FindMin(SearchTree t){
    if(t != NULL)
        while(t->left != NULL)
            t = t->left;
    return t;
}

SearchTree Insert(ElementType x, SearchTree t){
    if(t == NULL){
        t = malloc(sizeof(struct TreeNode));
        if(t == NULL){
            printf("Out of space!\n");
            exit(1);
        }
        t->element = x;
        t->left = t->right = NULL;
    }
    else if(t->element > x)
            t->left = Insert(x, t->left);
    else if(t->element < x)
            t->right = Insert(x, t->right);
    
    return t;
}

SearchTree Delete(ElementType x, SearchTree t){
    Position tmpCell;
    if(t == NULL){
        printf("Element not found!\n");
        exit(1);
    }
    else if(x < t->element)
        t->left = Delete(x, t->left);
    else if(x > t->element)
        t->right = Delete(x, t->right);
    else if(t->left && t->right){
        tmpCell = FindMin(t->right);
        t->element = tmpCell->element;
        t->right = Delete(t->element, t->right);
    }
    else{
        tmpCell = t;
        if(t->right == NULL)
            t = t->left;
        if(t->left == NULL)
            t = t->right;
        free(tmpCell);
    }
    return t;
}

void Traverse(SearchTree t){
    if(t != NULL){
        Traverse(t->left);
        printf("%d ", t->element);
        Traverse(t->right);
    }
}

int main(){
    SearchTree t = NULL;
    t = MakeEmpty(t);
    Position p;
    t = Insert(1, t);
    t = Insert(2, t);
    t = Insert(4, t);
    t = Insert(3, t);
    t = Insert(6, t);
    t = Insert(8, t);
    // p = FindMin(t);
    // printf("find: %d\n", p->element);
    t = Delete(1, t);
    Traverse(t);
    printf("\n");
    return 0;
}