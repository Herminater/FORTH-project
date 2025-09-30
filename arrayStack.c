#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>

int stackEnd = -1;
int stack[50];

int* pop(void){
    if (stackEnd == -1){
        return NULL;
    }
    int* holder = &stack[stackEnd];
    stackEnd--;
    return holder;
}

void push(int val){
    if (stackEnd == 49){
        return;
    }
    stackEnd++;
    stack[stackEnd] = val;
}

void printStack(void){
    //printf("%d %d ", stack[0], stackEnd);
    for (int i = 0; i <= stackEnd; i++){
        printf("%d ", stack[i]);
    }
    printf("\n");
}

void mult(){
    if (stackEnd > 0){
        int a = *pop();
        int b = *pop();
        push(a * b);
    }
}

void add(){
    if (stackEnd > 0){
        int a = *pop();
        int b = *pop();
        push(a + b);
    }
}

void sub(){
    if (stackEnd > 0){
        int a = *pop();
        int b = *pop();
        push(a - b);
    }
}

void div(){
    if (stackEnd > 0){
        int a = *pop();
        int b = *pop();
        push(b / a);
    }
}

void mod(){
    if (stackEnd > 0){
        int a = *pop();
        int b = *pop();
        push(b % a);
    }
}

void passString(char c[]){
    int left = 0;
    for (int right = 0; right<50; right++){
        if (c[right] = ' '){
            // tjek bagerste ting og bestem type ud fra det
            // ...




        }
    }


}

int main(void){

    bool flag = true;
    char c[100];
    int maxSize = 50;

    while (flag){
        //scanf("%c ", &c);
        fgets(c, maxSize, stdin);

        passString(c);

    //     //printf("%d", isdigit(c));
    //     if (c == 'q'){
    //         flag = false;
    //         return 0;
    //     }

    //     if (isdigit(c) != 0){
    //         push((int) (c-'0'));
    //     }
    //     else{
    //         //printf("Not Digit\n");
    //         switch (c){
    //             case '*':
    //                 //printf("Here");
    //                 mult();
    //                 break;
                
    //             case '+':
    //                 add();
    //                 break;

    //             case '-':
    //                 sub();
    //                 break;
                
    //             case '/':
    //                 div();
    //                 break;
                
    //             case '%':
    //                 mod();
    //                 break;
                
    //             default:
    //                 printf("Not recognised\n");
    //         }

    //     }
    //     printStack();
    }


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