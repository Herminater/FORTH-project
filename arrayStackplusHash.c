#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>
#include <math.h>
#include <string.h>
#include "hashmap_implementation.h"
#include "hashmap_implementation_string.h"

#define MAXSIZESTACK 200


int stackEnd = -1;
int stck[MAXSIZESTACK];
hashMap map;
hashMapString string_map;


int left;
int right;
int loop_counter;

int* pop(void){ 
    if (stackEnd == -1){
        return NULL;
    }
    int* holder = &stck[stackEnd];
    stackEnd--;
    return holder;
}
void push(int val){
    if (stackEnd == MAXSIZESTACK ){
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
    printf("\033[0;32m"); // source for codes and how to: https://medium.com/@selvarajk/adding-color-to-your-output-from-c-58f1a4dc4e75
    printf("- ok \n");
    printf("\033[0m");
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
        push(b || a);
    };
}
void INVERT(){
    if (stackEnd >= 0){
        int a = *pop();
        push(!a);
    };
}
void print(){ // .
    if (stackEnd >= 0){
        int a = *pop();
        printf("%d ", a);
    }
}
void EMIT(){ // int as ascii
    if (stackEnd >= 0){
        int a = *pop();
        printf("%c", (char)a);
    }
}
void CR(){
    printf("\n");
}
void dup(){
    if (stackEnd >= 0){
        int a = *pop();
        push(a);
        push(a);
    }
}
void drop(){
    if (stackEnd >= 0){
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
};
void printString(char c[], int* right, int* left){ 
    *right += 1; // tag højde for mellemrummet
    int i;
    for (i=0; i<strlen(c)-1; i++){
        if (c[*right+i] == '\"'){
            break;
        }
        printf("%c", c[*right+i]);
    }
    *right += i+1;
    *left = *right+1;
}
void define(char c[], int* right, int* left);
void passString(char c[]);

void i_counter(){

}

int find_subString(char c[], char s[], int start){
    bool flag = false;
    for (int i = start; i<strlen(c); i++){
        if (c[i] == s[0]){
            for (int j=1; j<strlen(s); j++){
                if (!(i+j<strlen(c) && c[i+j] == s[j])){
                    flag = true;
                    break;
                }
            }
            if (!flag){
                return i;
            }
            flag = false;
        }
    }

    return -1;
}

void loop(char c[], int *r){
    *r += 1; // mellemrum
    int start = *pop();
    int end = *pop();
    char loo[] = "loop\0";
    int idx_loop = find_subString(c, loo, *r);

    char new[MAXSIZESTACK]; // kan gøres til størrelse på right til idx_loop
    strncpy(new, c+*r, idx_loop-*r);

    int idx_left = left;
    int idx_right = right;
    for (loop_counter=start; loop_counter<end; loop_counter++){
        passString(new);
    }
    right = idx_loop+5; // slutmellemrum og loop;
    left = right;


}

void ifelse(char c[], int* right){
    int p = *pop();
    bool t = (p == 0) ? false : true;
    *right += 1; // mellemrum
    left = *right;
    char e[5] = "else\0";
    char th[5] = "then\0";
    char new[MAXSIZESTACK];

    int idx_then;
    int idx_else;
    // hvis t -> find then 
    idx_then = find_subString(c, th, *right);
    idx_else = find_subString(c, e, *right);
    if (idx_then == -1){
        printf("ERROR");
    }

    // hvis ikke t -> find else
    if (!t){
        if (idx_else != -1){
            strncpy(new, c+idx_else+5, idx_then-idx_else-4);
            passString(new);
        }
    }else{
        if (idx_else != -1){
            strncpy(new, c+left, idx_else-left);   
            passString(new);
        }
        else{
            strncpy(new, c+left, idx_then-left);   
            passString(new);
        }
    }
    
    *right = idx_then+5;
    left = *right;


}

// kører en custom funktion fra string_map og map
void custom(char c[]){
    int temp_left;
    int temp_right;
    temp_left = left;
    temp_right = right;

    char * function = get_string(&string_map, c);
    passString(function);

    left = temp_left;
    right = temp_right;
}

// deler strengen op i dele og pusher digits og kører funktioner
void passString(char c[]){
    left = 0;
    right = 0;
    int curr = 0;
    char curr_str[MAXSIZESTACK];

    for (; right<strlen(c); right++){ // kør så længe der er char i strengen
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
                curr_str[right-left] = '\000';
                void (*fptr)();
                fptr = get(&map, curr_str);

                if (fptr == &define){
                    fptr(c, &right, &left); // we need to define a function and update indexes after
                    continue;
                }

                else if (fptr == &printString){
                    fptr(c, &right, &left); // we need to parse the funktion and the pointers
                    continue;
                }

                else if (fptr == &custom){
                    fptr(curr_str);
                }

                else if (fptr == &ifelse){
                    fptr(c, &right);
                }

                else if (fptr == &loop){
                    fptr(c, &right);
                }

                else if (fptr == &i_counter){
                    push(loop_counter);
                }

                else if (fptr != NULL){
                    fptr();
                }
                else{
                    printf("\033[1;31m"); // source for color-code and how to : https://medium.com/@selvarajk/adding-color-to-your-output-from-c-58f1a4dc4e75
                    printf("%s - ?\n", curr_str); 
                    printf("\033[0m");
                    // printf("Letter is %c", c[right]);
                    return;
                }

            }
            left = right+1; // sæt left til starten af næste del af strengen
        }
        
    }
}

// definerer en ny custom funktion
void define(char c[], int* right, int* left){
    char k[MAXSIZESTACK];

    for (int i = 0; i<strlen(c)-1; i++){
        k[i] = '\000';
    }

    char funktion[MAXSIZESTACK ];
    int curr_left = *right + 1; // tag højde for mellemrum efter : 
    // find første mellemrum
    int i = 0;

    for (; i<strlen(c)-1; i++){
        if (c[curr_left+i] == ' '){
            strncpy(k, c+curr_left, i);
            break;
        }
    }
    // find semikolon
    int new_idx = curr_left+i ;
    for (; i<strlen(c); i++){
        if (c[curr_left+i] == ';'){
            strncpy(funktion, c+new_idx+1, curr_left+i-new_idx-1);
            break;
        }
    }


    put_string(&string_map, k, funktion);
    put(&map, k, &custom); 
    
    *right = curr_left+i+1;
    *left = *right;
    // 

}   


int main(void){
    // hashmap:
    map = init_hashMap();

    // definer basic functions
    put(&map, "*", &mult);
    put(&map, "/", &divid);
    put(&map, "+", &add);
    put(&map, "-", &sub);
    put(&map, "mod", &mod);
    put(&map, "=", &equals);
    put(&map, ">", &less);
    put(&map, "<", &more);
    put(&map, "and", &AND);
    put(&map, "or", &OR);
    put(&map, "invert", &INVERT);
    put(&map, ".", &print);
    put(&map, "emit", &EMIT);
    put(&map, "cr", &CR);
    put(&map, "dup", &dup);
    put(&map, "drop", &drop);
    put(&map, "swap", &swap);
    put(&map, "over", &over);
    put(&map, "rot", &rotate);
    put(&map, ":", &define);
    put(&map, ".\"", &printString);
    put(&map, "if", &ifelse);
    put(&map, "do", &loop);
    put(&map, "i", &i_counter);


    bool flag = true;
    char c[MAXSIZESTACK]; // holder nuværende input fra brugeren
    int maxSize = MAXSIZESTACK;

    while (flag){
        fgets(c, maxSize, stdin);
        int str_length = strlen(c);

        if (c[str_length-2] != ' '){ // sørger for mellemrum til sidst hvis glemt
            c[str_length-1] = ' ';
            c[str_length]= '\n';
            c[str_length+1] = '\000';

        }

        // behandler strengen
        passString(c);
        printStack();
    }


    return 1;
}
