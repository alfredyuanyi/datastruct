#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "arrayqueue.h"

#define MinQueueSize (4)

typedef struct Node * PtrToNode;

struct Node{
    ElementType element;
    PtrToNode next;
};

struct QueueRecord{
    PtrToNode rear;
    PtrToNode front;
    int size;
    int capacity;
};

int IsEmpty(Queue q){
    return q->size == 0;
}

int IsFull(Queue q){
    return q->size == q->capacity;
}

Queue CreateQueue(int queueSize){
    if(queueSize < MinQueueSize){
        printf("Queuesize is too small!\n");
        exit(1);
    }
    Queue q = malloc(sizeof(struct QueueRecord));
    if(q == NULL){
        printf("Out of space!\n");
        exit(1);
    }
    q->capacity = queueSize;
    q->size = 0;
    q->rear = NULL;
    q->front = NULL;
    MakeEmpty(q);
    return q;
}

void DisposeQueue(Queue q){
    MakeEmpty(q);
    free(q);    
}

void MakeEmpty(Queue q){
    if(q == NULL){
        printf("Create queue first!\n");
        exit(1);
    }
    while(!IsEmpty(q))
        Dequeue(q);
}

void Enqueue(ElementType x, Queue q){
    while(IsFull(q)){
        printf("Queue is full! Waiting for dequeueing...\n");
        sleep(1);
    }
    PtrToNode node = malloc(sizeof(struct Node));
    if(node == NULL){
        printf("Out of space!\n");
        exit(1);
    }
    node->next = NULL;
    node->element = x;
    if(q->size == 0){
        q->rear = node;
        q->front = node;
        q->size++;
    }
    else{
        q->rear->next = node;
        q->rear = node;
        q->size++;
    }
    
}

ElementType Front(Queue q){
    if(IsEmpty(q)){
        printf("Queue is empty!\n");
        exit(1);
    }
    return q->front->element;
}

ElementType FrontAndDequeue(Queue q){
    if(IsEmpty(q)){
        printf("Queue is empty!\n");
        exit(1);
    }
    PtrToNode node = q->front;
    ElementType value = node->element;
    q->front = node->next;
    free(node);
    q->size--;
    if(q->size == 0)
        q->rear = NULL;
    return value;
}

void Dequeue(Queue q){
    if(IsEmpty(q)){
        printf("Queue is empty!\n");
        exit(1);
    }
    PtrToNode node = q->front;
    q->front = node->next;
    free(node);
    q->size--;
    if(q->size == 0)
        q->rear = NULL;
}

int main(){
    Queue q = CreateQueue(4);
    Enqueue(1, q);
    Enqueue(2, q);
    Enqueue(3, q);
    Enqueue(4, q);
    Dequeue(q);
    Dequeue(q);
    Enqueue(5, q);
    printf("front is : %d\n",FrontAndDequeue(q));
    printf("front is : %d\n",FrontAndDequeue(q));
    DisposeQueue(q);
    return 0;
}