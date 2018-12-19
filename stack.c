#include <stdio.h>
#include <stdlib.h>

struct Stack{
    int count;
    struct Node *top;
};

struct Node{
    int value;
    struct Node *next;
};

typedef struct Node   *NODE_POINTER;
typedef struct Stack  *STACK_POINTER;

NODE_POINTER createNode(){
    NODE_POINTER newNode = (NODE_POINTER) malloc(sizeof(struct Node));
    return newNode;
}

STACK_POINTER createStack(){
    STACK_POINTER newStack = (STACK_POINTER) malloc(sizeof(struct Stack));
    newStack->count = 0;
    return newStack;
}

void push(STACK_POINTER stack,int value){
    NODE_POINTER newNode = createNode();
    newNode->value = value;
    newNode->next = stack->top;
    stack->top = newNode;
    stack->count++;
}

void printStack(STACK_POINTER stack){

    NODE_POINTER top = stack->top;

    for(int i = 0;i < stack->count;i++){
        printf(" %d ",top->value);
        top = top->next;
    }

}

int pop(STACK_POINTER stack){
    NODE_POINTER top = stack->top;
    int value = top->value;
    if(top == NULL){
        return -1;
    }
    stack->count--;
    stack->top = top->next;
    return value;
}

int main(int argc, char const *argv[])
{
    STACK_POINTER A = createStack();

    push(A,1);
    push(A,3);
    push(A,5);

    //printf("%d",A->top->value);

    printStack(A);

    pop(A);

    printStack(A);

    return 0;
}
