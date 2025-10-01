#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>
#include <math.h>
#include <string.h>
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

// deler strengen op i dele og pusher digits og kører funktioner
void passString(char c[]){
    int left = 0;
    int curr = 0;
    char curr_str[50];
    for (int right = 0; right<strlen(c)-1; right++){ // kør så længe der er char i strengen

        printf("Char is %c \n", c[right]);

        if (c[right] == ' '){ // hvis et mellemrum findes
            if (isdigit(c[left]) != 0){ // og det er et digit
                for(int i=0; i<right-left; i++){ // kør fra left til right og læg dem til med den rigtige potens
                    curr += (int)(c[left+i]-'0') * pow(10, right-left-1-i); // lægger tallet på left til ganget med en potens af 10
                }
                push(curr);
                curr = 0; // reset curr til næste gang et digit findes
            }
            else{
                strncpy(curr_str, c+left, right-left); // pas på med den her igen:) - overvej loop
                bool (*function)();

                void (*fptr)();
                fptr = &mult;
                fptr();
            }
            left = right+1; // sæt left til starten af næste del af strengen
        }
        
    }
    printStack();


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