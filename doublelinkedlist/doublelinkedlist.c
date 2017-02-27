#include "doublelinkedlist.h"
#include <stdio.h>
#include <stdlib.h>

// define the node of doublelinkedlist.
struct node{
    elementType element;
    position left;
    position right;
}Node;
elementType InputElement(){
    elementType x;
    printf("please input an element: ");
    scanf("%d", &x);
    return x;
}
position NewNode(){
    position p = malloc(sizeof(Node));
    if(p == NULL){
        printf("out of space!");
        exit(1);
    }
    p->element = InputElement();
    p->left = NULL;
    p->right = NULL;
    return p;
}
position NewEmptyNode(){
    position p = malloc( sizeof(Node) );
    if(p == NULL){
        printf("out of space!");
        exit(1);
    }
    p->left = NULL;
    p->right = NULL;
    return p;
}
// create a new doublelinkedlist which has a header pointer.
doubleLinkedList CreateDoubleLinkedList(){
    position p, r = NULL, l = NULL;
    char c;
    p=r=l=NewEmptyNode();
    printf("already create a new doublelinkedlist which has a header pointer,do you want input another element? y/n ");
    while(( c = getchar() ) == '\n');
    while(c != 'n'){
        r = NewNode();
        if(p == l){
            p->right = r;
            r->left = p;
        }
        else{
            l->right = r;
            r->left = l;
        }
        l = r;
        printf("input another element? y/n ");
        while(( c = getchar() ) == '\n');
    }
    return p;
}
void Traverse(doubleLinkedList L){
    if(L->right == NULL){
        printf("this doubleLinkedList is null\n");
        return;
    }
    position p = L->right; 
    while(p != NULL){
        printf("p->element = %d\n", p->element);
        p = p->right;
    }
}
int IsEmpty(doubleLinkedList DL){
    return DL->right == NULL;
}
int IsLast(position p, doubleLinkedList DL){
    return p->right == NULL;
}
int IsFirst(position p, doubleLinkedList DL){
    return DL->right == p;
}
// find X in DL, if not exist, return NULL.
position Find(elementType X, doubleLinkedList DL){
    position p = DL->right;
    while(p != NULL && p->element != X) p = p->right;
    return p;
}
// insert X into DL which is behind frontNode.
void Insert(elementType frontNxodeValue, elementType x, doubleLinkedList DL){
    position frontNode = Find(frontNxodeValue, DL);
    position xNode = NewEmptyNode();
    xNode->element = x;
    xNode->right = frontNode->right;
    xNode->left = frontNode->left;
    frontNode->right = xNode;
}
// delete x from DL, if not exist,then return;
void Remove(elementType x, doubleLinkedList DL){
    position targetNode = Find(x, DL);
    if(targetNode == NULL) {
        printf("%d does not exist in this DL.\n", x);
        return;
    }
    targetNode->left->right = targetNode->right;
    targetNode->right->left = targetNode->left;
    free(targetNode);
}
void Replace(elementType before, elementType after, doubleLinkedList DL){
    position beforeNode = Find(before, DL);
    if(beforeNode == NULL){
        printf("can not find element %d.\n", before);
        return;
    }
    beforeNode->element = after;
}
void DeleteList(doubleLinkedList DL){
    position p, temp;
    p = temp = DL->right;
    while(p != NULL){
        temp = p->right;
        free(p);
        p = temp;
    }
    DL->right = NULL;
}
int main(){
    doubleLinkedList l = CreateDoubleLinkedList();
    Traverse(l);
    DeleteList(l);
    printf("after deletelist\n");
    if(l == NULL) printf("l is null");
    Traverse(l);
    printf("hello, doublelinkedlist!\n");
    return 0;
}