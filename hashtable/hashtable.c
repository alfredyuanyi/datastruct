#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "hashtable.h"

#define MinTableSize (10)

int Gcd(unsigned int a, unsigned int b)
{
    int temp;
    while(b > 0)
    {
        temp = a % b;
        a = b;
        b = temp;
    }
    return a;
}

struct ListNode{
    ElementType element;
    Position next;
};
typedef Position List;

struct HashTbl{
    int tableSize;
    List *theLists;
};

int NextPrime(int tableSize){
    int i, j, temp;
    for(i = tableSize; ; i++){
        temp = sqrt(i);
        for(j = 2;j <= temp; j++){
            if(Gcd(j, i) != 1) break;
        }
        if(j > temp)
            return i;
    }
}

HashTable InitializeTable(int tableSize){
    HashTable h;
    int i;
    if(tableSize < MinTableSize){
        printf("Tablesize is too small!\n");
        exit(1);
    }
    h = malloc(sizeof(struct HashTbl));
    h->tableSize = NextPrime(tableSize);
    h->theLists = malloc(sizeof(List) * h->tableSize);
    for(i = 0; i < h->tableSize; i++){
        h->theLists[i] = malloc(sizeof(struct ListNode));
        if(h->theLists[i] == NULL){
            printf("Out of space!\n");
            exit(1);
        }
        h->theLists[i]->next = NULL;
    }
    return h;
}

void DeleteList(Position L)
{
	Position p, temp;
	p = L->next;
	L->next = NULL;
	while(p != NULL)
	{
		temp = p->next;
		free(p);
		p = temp;
	}
}

void DestroyTable(HashTable h){
    if(h == NULL)
        return;
    int i;
    for(i = 0; i < h->tableSize; i++){
        DeleteList(h->theLists[i]);
    }
    free(h->theLists);
}

int Hash(ElementType key, int tableSize){
    return key % tableSize;
}

Position Find(ElementType key, HashTable h){
    Position p;
    List l;
    l = h->theLists[Hash(key, h->tableSize)];
    p = l->next;
    while(p != NULL && p->element != key){
        p = p->next;
    }
    return p;
}

void Insert(ElementType key, HashTable h){
    Position p, newCell;
    List l;
    p = Find(key, h);
    if(p == NULL){
        newCell = malloc(sizeof(struct ListNode));
        if(newCell == NULL){
            printf("Out of space!\n");
            exit(1);
        }
        l = h->theLists[Hash(key, h->tableSize)];
        newCell->next = l->next;
        newCell->element = key;
        l->next = newCell;
    }
}

ElementType Retrieve(Position p){
    if(p == NULL){
        printf("NULL Position!\n");
        exit(1);
    }
    return p->element;
}

// gcc编译时,加上 -lm
int main(){
    HashTable h = InitializeTable(10);
    Insert(1, h);
    Insert(3, h);
    Insert(6, h);
    Insert(2, h);
    Position p = Find(2, h);
    printf("%d\n", p->element);
    DestroyTable(h);
    return 0;
}