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

int* pop(void){ // problem ved 1 item i stacken
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
    printf("- ok \n");
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
    if (stackEnd >= 0){
        int a = *pop();
        push(!a);
    };
}
void print(){ // .
    if (stackEnd >= 0){
        int a = *pop();
        printf("%d\n", a);
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
void printString(char c[], int* right, int* left){ // fejlen virker til at lægge i indexeringen i parsestringfunktionen, da ." aldrig køres
    *right += 1; // tag højde for mellemrummet
    int i;
    for (i=0; i<strlen(c)-1; i++){
        if (c[*right+i] == '\"'){
            break;
        }
        printf("%c", c[*right+i]);
    }
    printf("\n");
    *right += i+1+2;
}
void define(char c[], int* right, int* left);
void passString(char c[]);

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
                curr_str[right] = '\000';
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

                else if (fptr != NULL){
                    fptr();
                }
                else{
                    printf("%s - ?\n", curr_str);
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

    // printf("DEFINE");

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
    put(&map, "*", &mult);
    put(&map, "/", &divid);
    put(&map, "+", &add);
    put(&map, "-", &sub);
    put(&map, "%", &mod);
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

    bool flag = true;
    char c[MAXSIZESTACK];
    int maxSize = MAXSIZESTACK;

    while (flag){
        fgets(c, maxSize, stdin);
        int str_length = strlen(c);

        if (c[str_length-2] != ' '){ // sørger for mellemrum til sidst
            c[str_length-1] = ' ';
            c[str_length]= '\n';
            c[str_length+1] = '\000';

        }

      
        // printf("%s", c);
        passString(c);
        printStack();
    }


    return 1;
}
