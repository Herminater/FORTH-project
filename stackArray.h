#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#define STACKMAXSIZE 200

typedef struct Stack{
    int stackEnd;
    int * list[STACKMAXSIZE];
} Stack;

Stack * init_stack(){
    Stack * stck = (Stack *) malloc(sizeof(Stack)); 
    stck->stackEnd = -1;
    return stck;
}

bool is_empty(Stack * stck){
    return stck->stackEnd == -1;
}

int pop(Stack * stck){ // retunerer VÆRDIEN af sidste element og fjerne det fra stacken
    if (stck->stackEnd == -1){
        printf("Stack is empty!");
        return -1;
    }
    int holder = *(stck->list[stck->stackEnd]);
    stck->stackEnd--;
    return holder;
}

void push(Stack * stck, int val){ // laver ny integer pointe
    int * v = (int *)malloc(sizeof(int));
    *v = val;
    if (stck->stackEnd == STACKMAXSIZE-1){
        printf("Stack is full");
        return;
    }
    stck->stackEnd += 1;
    stck->list[stck->stackEnd] = v;
}

int * peek(Stack * stck){
    if (stck->stackEnd == -1){
        return NULL;
    }
    int * p = stck->list[stck->stackEnd];
    return p;
}

void push_existing(Stack * stck, int * val){
    if (stck->stackEnd == STACKMAXSIZE-1){
        printf("Stack is full");
        return;
    }
    stck->stackEnd += 1;
    stck->list[stck->stackEnd] = val;
}

void printStack(Stack * stck){
    printf("\n");
    for (int i = 0; i <= stck->stackEnd; i++){
        printf("%d ", *(stck->list[i]));
    }
    printf("\033[0;32m"); // source for codes and how to: https://medium.com/@selvarajk/adding-color-to-your-output-from-c-58f1a4dc4e75
    printf("- ok \n");
    printf("\033[0m");
}