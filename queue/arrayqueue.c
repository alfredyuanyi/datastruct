#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "arrayqueue.h"

#define MinQueueSize (5)

struct QueueRecord{
    int capacity;
    int front;
    int rear;
    int size;
    ElementType *array;
};

int IsEmpty(Queue q){
    return q->size == 0;
}

int IsFull(Queue q){
    return q->size == q->capacity;
}

void MakeEmpty(Queue q){
    q->size = 0;
    q->front = 0;
    q->rear = -1;
}

void DisposeQueue(Queue q){
    if(q != NULL){
        free(q->array);
        free(q);
    }
}

Queue CreateQueue(int queueSize){
    Queue q = malloc(sizeof(struct QueueRecord));
    if(q == NULL){
        printf("Out of space!\n");
        exit(1);
    }
    if(queueSize < MinQueueSize){
        printf("Queuesize is too small!\n");
        exit(1);
    }
    q->array = malloc(sizeof(ElementType) * queueSize);
    if(q->array == NULL){
        printf("Out of space!\n");
        exit(1);
    }
    q->capacity = queueSize;
    MakeEmpty(q);
    return q;
}

void Enqueue(ElementType x, Queue q){
    while(IsFull(q)){
        printf("Queue is Full! Waiting for dequeueing!\n");
        sleep(1);
    }
    q->size++;
    q->rear = ++q->rear % q->capacity;
    q->array[q->rear] = x;
}

ElementType Front(Queue q){
    if(IsEmpty(q)){
        printf("Queue is empty!\n");
        exit(1);
    }
    return q->array[q->front];
}

void Dequeue(Queue q){
    if(IsEmpty(q)){
        printf("Queue is empty!");
        exit(1);
    }
    q->size--;
    q->front = ++q->front % q->capacity;
}

ElementType FrontAndDequeue(Queue q){
    if(IsEmpty(q)){
        printf("Queue is empty!");
        exit(1);
    }
    q->size--;
    ElementType front = q->array[q->front];
    q->front = ++q->front % q->capacity;
    return front;

}

int main(){
    Queue q = CreateQueue(5);
    Enqueue(1, q);
    Enqueue(2, q);
    Enqueue(3, q);
    Enqueue(4, q);
    Enqueue(5, q);
    Dequeue(q);
    printf("IsFull: %d\n", IsFull(q));
    Enqueue(6, q);
    Enqueue(7, q);
    Dequeue(q);
    printf("Queue's front is %d\n", FrontAndDequeue(q));
    DisposeQueue(q);
    return 0;
}