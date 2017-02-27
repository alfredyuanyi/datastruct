#include <stdio.h>
#include <stdlib.h>

#include "linkedliststack.h"

struct Node{
    ElementType element;
    PtrToNode next;
};

int IsEmpty(Stack s){
    return s->next == NULL;
}

void Pop(Stack s){
    if(IsEmpty(s)){
        printf("Empty stack!\n");
        exit(1);
    }
    PtrToNode node = s->next;
    s->next = node->next;
    free(node);
}

void MakeEmpty(Stack s){
    if(s == NULL){
        printf("Must use CreateStack first!\n");
        exit(1);
    }
    else{
        while(!IsEmpty(s))
            Pop(s);
    }
}

Stack CreateStack(void){
    Stack s;
    s = malloc(sizeof(struct Node));
    if(s == NULL){
        printf("Out of space!\n");
        exit(1);
    }
    s->next = NULL;
    MakeEmpty(s);
    return s;
}

void DisposeStack(Stack s){
    MakeEmpty(s);
    free(s);
}

void Push(ElementType x, Stack s){
    PtrToNode node = malloc(sizeof(struct Node));
    if(node == NULL){
        printf("Out of space!");
        exit(1);
    }
    node->element = x;
    node->next = s->next;
    s->next = node;
}

ElementType Top(Stack s){
    if(IsEmpty(s)){
        printf("Empty stack!");
        return 0;
    }
    return s->next->element;
}

ElementType TopAndPop(Stack s){
    if(IsEmpty(s)){
        printf("Empty stack!");
        return 0;
    }
    PtrToNode node = s->next;
    ElementType x = node->element;
    s->next = node->next;
    free(node);
    return x;
}

void InfixToPostfix(char *infix, Stack result, int N){
    Stack s = CreateStack();  
    int i;
    for(i = 0; i < N; i++){
        if(infix[i] == '*' || infix[i] == '(')
            Push(infix[i], s);
        else if(infix[i] == '+'){
            if(IsEmpty(s)){
                Push(infix[i], s);
                continue;
            }
            char ch = Top(s);
            while(ch == '*' || ch == '+'){
                Push(TopAndPop(s), result);
                if(IsEmpty(s)){
                    break;
                }
                ch = Top(s);
            }
            Push(infix[i], s);
        }
        else if(infix[i] == ')'){
            char temp = Top(s);
            while(temp != '('){
                Push(TopAndPop(s), result);
                temp = Top(s);
            }   
            Pop(s);
            if(i == N - 1){
                while(!IsEmpty(s))
                    Push(TopAndPop(s), result);
            }
        }
        else{
            Push(infix[i], result);
            if(i == N - 1){
                while(!IsEmpty(s))
                    Push(TopAndPop(s), result);
            }
        }
    }  
}
int main(){
    Stack s = CreateStack();
    Stack result = CreateStack();
    char infix[15] = {"a+b*c+(d*e+f)*g"};
    InfixToPostfix(infix, result, 15);
    int i = 0;
    while(!IsEmpty(result)){
        // infix[i] = TopAndPop(result);
        // i++;
        printf("%c", TopAndPop(result));
    }
    printf("\n");
    // printf("%s\n", infix);
    DisposeStack(s);
    // char str[5] = {"a + b"};
    // char *p = str;
    // printf("%s\n", p);
    // scanf("%s", p);
    // printf("%s\n", p);
    return 0;
}