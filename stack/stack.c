#include <stdio.h>
#include <stdlib.h>

#include "stack.h"

#define EmptyTOS (-1)
#define MinStackSize (5)

struct StackRecord{
    int capacity;
    int topOfStack;
    ElementType *array;
};
int IsEmpty(Stack s){
    return s->topOfStack == EmptyTOS;
}

int IsFull(Stack s){
    return s->topOfStack == (s->capacity -1);
}

void MakeEmpty(Stack s){
    s->topOfStack = EmptyTOS;
}

Stack CreateStack(int maxElements){
    Stack s;
    if(maxElements < MinStackSize){
        printf("Stack size is too small!\n");
        exit(1);
    }
    s = malloc(sizeof(struct StackRecord));
    if(s == NULL){
        printf("Out of space!\n");
        exit(1);
    }
    s->array = malloc(sizeof(ElementType) * maxElements);
    if(s->array == NULL){
        printf("Out of space!\n");
        exit(1);
    }
    s->capacity = maxElements;
    MakeEmpty(s);
    return s;
}

void DisposeStack(Stack s){
    if(s != NULL){
        free(s->array);
        free(s);
    }
}

void Push(ElementType x, Stack s){
    if(IsFull(s)){
        printf("Stack is full!\n");
        exit(1);
    }
    else{
        s->array[++s->topOfStack] = x;
    }
}

ElementType Top(Stack s){
    if(IsEmpty(s)){
        printf("Stack is Empty!\n");
        return 0;
    }
    else{
        return  s->array[s->topOfStack];
    }
}

void Pop(Stack s){
    if(IsEmpty(s)){
        printf("Stack is empty!\n");
        exit(1);
    }
    else
        s->topOfStack--;
}

ElementType TopAndPop(Stack s){
    if(IsEmpty(s)){
        printf("Stack is empty!\n");
        return 0;
    }
    else   
        return s->array[s->topOfStack--];
}

int main(){
    Stack s = CreateStack(6);
    printf("IsEmpty: %d\n", IsEmpty(s));
    printf("IsFull: %d\n", IsFull(s));
    Push(1, s);
    Push(2, s);
    Push(3, s);
    Push(4, s);
    Push(5, s);
    Push(6, s);
    ElementType a = TopAndPop(s);
    printf("Top is %d\n", a);
    a = Top(s);
    DisposeStack(s);
    return 0;
}