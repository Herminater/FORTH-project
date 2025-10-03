#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>
#include <math.h>
#include <string.h>
#include "hashmap_implementation.h"

int stackEnd = -1;
int stck[50];
hashMap map;

int* pop(void){
    if (stackEnd == -1){
        return NULL;
    }
    int* holder = &stck[stackEnd];
    stackEnd--;
    return holder;
}

void push(int val){
    if (stackEnd == 49){
        return;
    }
    stackEnd++;
    stck[stackEnd] = val;
}

void printStack(void){
    //printf("%d %d ", stack[0], stackEnd);
    for (int i = 0; i <= stackEnd; i++){
        printf("%d ", stck[i]);
    }
    printf("\n");
}

void mult(){
    if (stackEnd > 0){
        int a = *pop();
        int b = *pop();
        push(a * b);
    };
}

void add(){
    if (stackEnd > 0){
        int a = *pop();
        int b = *pop();
        push(a + b);
    };
}

void sub(){
    if (stackEnd > 0){
        int a = *pop();
        int b = *pop();
        push(b - a);
    };
}

void divid(){
    if (stackEnd > 0){
        int a = *pop();
        int b = *pop();
        push(b / a);
    };
}

void mod(){
    if (stackEnd > 0){
        int a = *pop();
        int b = *pop();
        push(b % a);
    };
}

void equals(){ // =
    if (stackEnd > 0){
        int a = *pop();
        int b = *pop();
        push(b == a);
    };
}

void less(){ // >
    if (stackEnd > 0){
        int a = *pop();
        int b = *pop();
        push(a < b);
    };
}

void more(){ // <
    if (stackEnd > 0){
        int a = *pop();
        int b = *pop();
        push(b < a);
    };
}

void AND(){
    if (stackEnd > 0){
        int a = *pop();
        int b = *pop();
        push(b && a);
    };
}

void OR(){
    if (stackEnd > 0){
        int a = *pop();
        int b = *pop();
        push(b && a);
    };
}

void INVERT(){
    if (stackEnd > 0){
        int a = *pop();
        push(!a);
    };
}

void print(){ // .
    if (stackEnd > 0){
        int a = *pop();
        printf("%d", a);
    }
}

void EMIT(){ // int as ascii
    if (stackEnd > 0){
        int a = *pop();
        printf("%c", (char)a);
    }
}

void CR(){
    printf("\n");
}

void dup(){
    if (stackEnd > 0){
        int a = *pop();
        push(a);
        push(a);
    }
}

void drop(){
    if (stackEnd > 0){
        pop();
    }
}

void swap(){
    if (stackEnd > 0){
        int a = *pop();
        int b = *pop();
        push(a);
        push(b);
    }
}

void over(){
    if (stackEnd > 0){
        int a = *pop();
        int b = *pop();
        push(a);
        push(b);
        push(a);
    }
}

void rotate(){
    if (stackEnd > 1){
        int a = *pop();
        int b = *pop();
        int c = *pop();
        push(b);
        push(c);
        push(a);
    }
}



// deler strengen op i dele og pusher digits og kører funktioner
void passString(char c[]){
    int left = 0;
    int curr = 0;
    char curr_str[50];
    for (int right = 0; right<strlen(c)-1; right++){ // kør så længe der er char i strengen

        // printf("Char is %c \n", c[right]);

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
                void (*fptr)();
                fptr = get(&map, curr_str);
                fptr();
            }
            left = right+1; // sæt left til starten af næste del af strengen
        }
        
    }
    printStack();
    printf("\n");


}

int main(void){
    // hashmap:
    map = init_hashMap();
    put(&map, "*", &mult);
    put(&map, "/", &divid);
    put(&map, "+", &add);
    put(&map, "-", &sub);
    put(&map, "%", &mod);
    put(&map, "=", &equals);
    put(&map, ">", &less);
    put(&map, "<", &more);
    put(&map, "AND", &AND);
    put(&map, "OR", &OR);
    put(&map, "INVERT", &INVERT);
    put(&map, ".", &print);
    put(&map, "EMIT", &EMIT);
    put(&map, "CR", &CR);
    put(&map, "DUP", &dup);
    put(&map, "DROP", &drop);
    put(&map, "SWAP", &swap);
    put(&map, "OVER", &over);
    put(&map, "ROTATE", &rotate);

    bool flag = true;
    char c[100];
    int maxSize = 50;

    while (flag){
        fgets(c, maxSize, stdin);
        passString(c);
    }


    return 1;
}
