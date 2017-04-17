#include <stdio.h>
#include <stdlib.h>

typedef struct Node *Position;
typedef struct HashTbl *HashTable;

#define MinTableSize (2)

struct Node{
    char *name;
    int id;
    Position next;
};
struct HashTbl{
    int tableSize;
    Position *list;
};

int Gcd(int a, int b){
    
}

HashTable InitializeTable(int tableSize){
    HashTable h;
    int i;
    h = (HashTable)malloc(sizeof(struct HashTbl));
    if(h == NULL){
        printf("Out of space!\n");
        return h;
    }
    if(tableSize < MinTableSize){
        printf("TableSize is too small!\n");
        return NULL;
    }
    //找大于tableSize的最小素数
    h->tableSize = NextPrime(tableSize);
    h->list = (Position*)malloc(sizeof(struct Node) * h->tableSize);
    if(h->list == NULL){
        printf("Out of space!\n");
        return NULL;
    }
    for(i = 0; i < h->tableSize; i++)
        h->list[i]->next = NULL;
    return h;
}

int main(){
    
    return 0;
}
