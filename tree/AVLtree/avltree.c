#include <stdio.h>
#include <stdlib.h>

#include "avltree.h"
struct AvlNode{
    ElementType element;
    AvlTree left;
    AvlTree right;
    int height;
};

AvlTree MakeEmpty(AvlTree t){
    if(t != NULL){
        MakeEmpty(t->left);
        MakeEmpty(t->right);
        free(t);
    }
    return NULL;
}

Position Find(ElementType x, AvlTree t){
    if(t == NULL)
        return NULL;
    if(t->element == x)
        return t;
    else if(t->element > x)
        return Find(x, t->left);
    else
        return Find(x, t->right);
}

Position FindMin(AvlTree t){
    if(t == NULL)
        return NULL;
    else
        while(t->left)
            t = t->left;
    return t;
}

Position FindMax(AvlTree t){
    if(t == NULL)
        return NULL;
    else
        while(t->right)
            t = t->right;
    return t;
}

static int Height(Position t){
    if(t == NULL)
        return -1;
    else
        return t->height;
}

int Max(int a, int b){
    return a > b?a:b;
}

AvlTree SingleRotateWithLeft(AvlTree t){
    AvlTree node = t->left;
    AvlTree node2 = t;
    node2->left = node->right;
    node->right = node2;
    node2->height = Max(Height(node2->left), Height(node2->right)) + 1;
    node->height = Max(Height(node->left), node2->height) + 1;
    return node;
}

AvlTree SingleRotateWithRight(AvlTree t){
    AvlTree node = t->right;
    AvlTree node2 = t;
    node2->right = node->left;
    node->left =node2;
    node2->height = Max(Height(node2->left), Height(node2->right)) + 1;
    node->height = Max(Height(node2->right), node->height) + 1;
    return node;
}

AvlTree DoubleRotateWithLeft(AvlTree t){
    Position node = t;
    Position node2 = t->left;
    Position node3 = node2->right;
    node2->right = node3->left;
    node3->left = node2;
    node->left = node3->right;
    node3->right = node;
    node->height = Max(Height(node->left), Height(node->right)) + 1;
    node2->height = Max(Height(node2->left), Height(node2->right)) + 1;
    node3->height = Max(node2->height, node->height) + 1;
    return node3;
}

AvlTree DoubleRotateWithRight(AvlTree t){
    Position node = t;
    Position node2 = t->right;
    Position node3 = node2->left;
    node2->left = node3->right;
    node3->right = node2;
    node->right = node3->left;
    node3->left = node;
    node->height = Max(Height(node->left), Height(node->right)) + 1;
    node2->height = Max(Height(node2->left), Height(node2->right)) + 1;
    node3->height = Max(node->height, node2->height) + 1;
    return node3;
}

AvlTree Insert(ElementType x, AvlTree t){
    if(t == NULL){
        t = malloc(sizeof(struct AvlNode));
        if(t == NULL){
            printf("Out of space!\n");
            exit(1);
        }
        t->element = x;
        t->left = t->right = NULL;
        t->height = 0;
    }
    else if(t->element > x){
        t->left = Insert(x, t->left);
        if(Height(t->left) - Height(t->right) == 2)
            if(x < t->left->element)
                t = SingleRotateWithLeft(t);
            else
                t = DoubleRotateWithLeft(t);
    }
    else if(t->element < x){
        t->right = Insert(x, t->right);
        if(Height(t->right) - Height(t->left) == 2)
            if(x > t->right->element)
                t = SingleRotateWithRight(t);
            else
                t = DoubleRotateWithRight(t);
    }
    t->height = Max(Height(t->left), Height(t->right)) + 1;
    return t;
}

AvlTree ResetHeightAndRotate(AvlTree t){
    if(t != NULL){
        t->height = Max(Height(t->left), Height(t->right)) + 1;
        if(Height(t->left) - Height(t->right) == 2)
            t = SingleRotateWithLeft(t);
        if(Height(t->right) - Height(t->left) == 2)
            t = SingleRotateWithRight(t);
    }
    return t;
}

AvlTree Delete(ElementType x, AvlTree t){
    if(t == NULL){
        printf("Not found element %d\n", x);
        exit(1);
    }
    else if(x < t->element){
        t->left = Delete(x, t->left);
        t = ResetHeightAndRotate(t);
    }
    else if(x > t->element){
        t->right = Delete(x, t->right);
        t->height = Max(Height(t->left), Height(t->right)) + 1;
        t = ResetHeightAndRotate(t);
    }
    else if(t->left && t->right){
        AvlTree temp = FindMin(t->right);
        t->element = temp->element;
        t->right = Delete(t->element, t->right);
        t = ResetHeightAndRotate(t);
    }
    else{
        AvlTree temp = t;
        if(t->left == NULL)
            t = t->right;
        else if(t->right == NULL)
            t = t->left;
        free(temp);
    }
    return t;
}

void Traverse(AvlTree t){
    if(t){
        Traverse(t->left);
        printf("%d ", t->element);
        Traverse(t->right);
    }
}

void CheckHeight(AvlTree t){
    if(t == NULL)
        return;
    if(Height(t->left) - Height(t->right) > 1)
        printf("wrong height!\n");
    else if(Height(t->right) - Height(t->left) > 1)
        printf("wrong height!\n");
    else{
        CheckHeight(t->left);
        CheckHeight(t->right);
    }
}

ElementType Retrieve(Position p){
    if(p == NULL){
        printf("NULL Position!\n");
        return 0;
    }
    return p->element;
}

int main(){
    AvlTree t;
    t = Insert(3, t);t = Insert(2, t);t = Insert(1, t);
    t = Insert(4, t);
    t = Insert(5, t);
    // t = Insert(6, t);
    // t = Insert(7, t);
    // t = Insert(15, t);
    // t = Insert(16, t);
    // t = Insert(14, t);
    Traverse(t);
    printf("\n");
    t = Delete(5, t);
    CheckHeight(t);
    Traverse(t);
    printf("\n");
    return 0;
}