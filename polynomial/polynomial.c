#include <stdio.h>
#include <stdlib.h>

#include "polynomial.h"

struct Node {
    int Cofficient;
    int Exponent;
    PtrToNode Next;
};



PtrToNode NewNode(){
    PtrToNode p;
    p = malloc( sizeof( PtrToNode ) );
    if(p == NULL)
    {
        printf("out of space!");
        exit(1);
    }
    printf("input Cofficient\n");
    scanf("%d", &(p->Cofficient));
    printf("input Exponent\n");
    scanf("%d", &(p->Exponent));
    p->Next = NULL;
    return p;
}

PtrToNode NewEmptyNode(){
    PtrToNode p;
    p = malloc( sizeof( PtrToNode ) );
    if(p == NULL)
    {
        printf("out of space!");
        exit(1);
    }
    p->Cofficient = 0;
    p->Exponent = 0;
    p->Next = NULL;
    return p;
}

Polynomial NewPolynomial(){
    PtrToNode p = NewEmptyNode();
    return p;
}

void Traverse(Polynomial p){
    PtrToNode temp = p->Next;
    while(temp){
        printf("Cofficient=%d, Exponent=%d\n", temp->Cofficient, temp->Exponent);
        temp = temp->Next;
    }
}

void AddPolynomial(const Polynomial p1,
                const Polynomial p2,
                Polynomial p){
    PtrToNode temp = p1->Next;
    PtrToNode ptemp = p;
    while(temp){
        PtrToNode node = NewEmptyNode();
        node->Cofficient = temp->Cofficient;
        node->Exponent = temp->Exponent;
        ptemp->Next = node;
        ptemp = node;
        temp = temp->Next;
    }
    temp = p2->Next;
    ptemp = p;
    while(temp){
        while(ptemp){
            if(ptemp->Next == NULL){
                PtrToNode node = NewEmptyNode();
                node->Exponent = temp->Exponent;
                node->Cofficient = temp->Cofficient;
                node->Next = ptemp->Next;
                ptemp->Next = node;
                break;
            }
            if(ptemp->Next->Exponent == temp->Exponent){
                ptemp->Next->Cofficient += temp->Cofficient;
                break;
            }
            else if(ptemp->Next->Exponent < temp->Exponent){
                PtrToNode node = NewEmptyNode();
                node->Exponent = temp->Exponent;
                node->Cofficient = temp->Cofficient;
                node->Next = ptemp->Next;
                ptemp->Next = node;
                break;
            }
            else{
                ptemp = ptemp->Next;
            }   
        }
        temp = temp->Next;
    }
}

void MultPolynomial(const Polynomial p1,
                const Polynomial p2,
                Polynomial p){
    PtrToNode temp = p2->Next;
    PtrToNode ptemp = p1;
    int i = 0;
    while(temp){
        Polynomial tempPoly = NewPolynomial();
        PtrToNode tempnode = tempPoly;
        ptemp = p1->Next;
        while(ptemp){
            PtrToNode node = NewEmptyNode();
            node->Cofficient = temp->Cofficient * ptemp->Cofficient;
            node->Exponent = temp->Exponent + ptemp->Exponent;
            tempnode->Next = node;
            tempnode = node;
            ptemp = ptemp->Next;
        }
        
        if(i == 0){
            p->Next = tempPoly->Next;
        }
        else{
            Polynomial tempSum = NewPolynomial();
            AddPolynomial(p,tempPoly, tempSum);
            p->Next = tempSum->Next;
        }
        i++;
        // printf("i = %d\n", i);
        // Traverse(p);
        temp = temp->Next;
    }
    
        
    // return p;
}

int main()
{
    Polynomial p = NewPolynomial();
    Polynomial p1 = NewPolynomial();
    Polynomial p2 = NewPolynomial();
    Polynomial node1 = NewEmptyNode();
    Polynomial node2 = NewEmptyNode();
    Polynomial node3 = NewEmptyNode();
    Polynomial node4 = NewEmptyNode();
    Polynomial node5 = NewEmptyNode();
    Polynomial node6 = NewEmptyNode();
    Polynomial node7 = NewEmptyNode();
    node1->Cofficient = 1;
    node1->Exponent = 4;
    node2->Cofficient = 1;
    node2->Exponent = 3;
    node3->Cofficient = 1;
    node3->Exponent = 2;
    node4->Cofficient = 1;
    node4->Exponent = 1;
    node5->Cofficient = 1;
    node5->Exponent = 6;
    node6->Cofficient = 1;
    node6->Exponent = 3;
    node7->Cofficient = 1;
    node7->Exponent = 2;
    p1->Next = node1; node1->Next = node2; node2->Next = node3; node3->Next = node4;
    p2->Next = node5; node5->Next = node6; node6->Next = node7;
    // printf("p1:\n");
    // Traverse(p1);
    // printf("p2:\n");
    // Traverse(p2);
    MultPolynomial(p1, p2,p);
    printf("p:\n");
    Traverse(p);
    return 0;
}