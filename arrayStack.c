#include <stdio.h>

int stackEnd = -1;
int stack[50];

int pop(void){
    int holder = stack[stackEnd];
    stackEnd--;
    return holder;
}

void push(int val){
    stackEnd++;
    stack[stackEnd] = val;
}

void printStack(void){
    //printf("%d %d ", stack[0], stackEnd);
    for (int i = 0; i <= stackEnd; i++){
        printf("%d ", stack[i]);
    }
}

int main(void){

    push(31);
    push(35);

    printStack();

    return 1;
}






/*typedef struct stack{
    char s[50][1];
    int pointer;
} stack;

stack intialize(){
    stack s;
    s.pointer = 0;
    //char st[50];
    //s.s = st;
}

char pop(stack *s){
    char StackEnd = s->s[s->pointer];
    s->pointer--;
    return StackEnd;
}

void push(stack *s, char c){
    s->pointer++;
    s->s[s->pointer] = c;
}

void printStack(stack *s){
    for (int i = 0; i <= s->pointer; i++){
        printf("%c ", &s->s[s->pointer]);
    }
}

int main(void){
    stack s = intialize();
    push(&s, '3');
    printStack(&s);
}
*/