#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>
#include <math.h>
#include <string.h>
#include "hashmap_implementation.h"
#include "hashmap_implementation_string.h"

#define MAXSIZESTACK 200

typedef struct element{
    int val;
    char s[200];
} element;


int stackEnd = -1;
int stck[MAXSIZESTACK];

hashMap map; // predefined functions
hashMapString string_map; // custom function-values

int left; // global left og right -pointer til user-inputted string
int right;
int loop_counter; // loop-counter til loops

int* pop(void){ // popper fra stacken og retunerer pointer til det poppede
    if (stackEnd == -1){
        return NULL;
    }
    int* holder = &stck[stackEnd];
    stackEnd--;
    return holder;
}
void push(int val){ // pusher til stacken
    if (stackEnd == MAXSIZESTACK ){
        return;
    }
    stackEnd++;
    stck[stackEnd] = val;
}
void printStack(void){ // printer stacken
    //printf("%d %d ", stack[0], stackEnd);
    for (int i = 0; i <= stackEnd; i++){
        printf("%d ", stck[i]);
    }
    printf("\033[0;32m"); // source for codes and how to: https://medium.com/@selvarajk/adding-color-to-your-output-from-c-58f1a4dc4e75
    printf("- ok \n");
    printf("\033[0m");
}
void mult(){ // popper 2 værdier fra stacken og pusher produktet
    if (stackEnd > 0){
        int a = *pop();
        int b = *pop();
        push(a * b);
    };
}
void add(){ // popper 2 værdier fra stacken og pusher summen
    if (stackEnd > 0){
        int a = *pop();
        int b = *pop();
        push(a + b);
    };
}
void sub(){ // popper 2 værdier fra stacken og pusher differencen
    if (stackEnd > 0){
        int a = *pop();
        int b = *pop();
        push(b - a);
    };
}
void divid(){ // popper 2 værdier fra stacken og pusher de to tal divideret
    if (stackEnd > 0){
        int a = *pop();
        int b = *pop();
        push(b / a);
    };
}
void mod(){ // popper 2 værdier fra stacken og pusher moduluproduktet
    if (stackEnd > 0){
        int a = *pop();
        int b = *pop();
        push(b % a);
    };
}
void equals(){ // popper 2 værdier fra stacken og pusher om de er ens
    if (stackEnd > 0){
        int a = *pop();
        int b = *pop();
        push(b == a);
    };
}
void less(){ // > popper 2 værdier fra stacken og pusher om toppen af stacken er mindre end anden øverst
    if (stackEnd > 0){
        int a = *pop();
        int b = *pop();
        push(a < b);
    };
}
void more(){ // < popper 2 værdier fra stacken og pusher om toppen af stacken er større end anden øverst
    if (stackEnd > 0){
        int a = *pop();
        int b = *pop();
        push(b < a);
    };
}
void AND(){ // popper 2 værdier fra stacken og pusher om de er ens
    if (stackEnd > 0){
        int a = *pop();
        int b = *pop();
        push(b && a);
    };
}
void OR(){ // popper 2 værdier fra stacken og pusher om en af de er sande
    if (stackEnd > 0){
        int a = *pop();
        int b = *pop();
        push(b || a);
    };
}
void INVERT(){ // pusher modsat boolean value af topværdien
    if (stackEnd >= 0){
        int a = *pop();
        push(!a);
    };
}
void print(){ // .  popper og printer
    if (stackEnd >= 0){
        int a = *pop();
        printf("%d ", a);
    }
}
void EMIT(){ // int as ascii.  popper og printer som ascii
    if (stackEnd >= 0){
        int a = *pop();
        printf("%c", (char)a);
    }
}
void CR(){ // linjeskift
    printf("\n");
}
void dup(){ // duplikerer top-værdien
    if (stackEnd >= 0){
        int a = *pop();
        push(a);
        push(a);
    }
}
void drop(){ // popper topværdien
    if (stackEnd >= 0){
        pop();
    }
}
void swap(){ // swapper de to øverste
    if (stackEnd > 0){
        int a = *pop();
        int b = *pop();
        push(a);
        push(b);
    }
}
void over(){ // tager anden øverste og dupper og pusher den
   if (stackEnd > 0){
        int a = *pop();
        int b = *pop();
        push(a);
        push(b);
        push(a);
    }
}
void rotate(){ // roterer øverste tre værdier
    if (stackEnd > 1){
        int a = *pop();
        int b = *pop();
        int c = *pop();
        push(b);
        push(c);
        push(a);
    }
};

void printString(char c[], int* right, int* left){  // tager en streng og printer fra venstre til højre

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
void define(char c[], int* right, int* left); // prototype
void passString(char c[]); // prototype

void i_counter(){ // adressen bruges bare til at parse korrekt funktion.

}

int find_subString(char c[], char s[], int start){ // finder substring og retunerer første index, hvis substring ikke findes retuneres -1
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

void loop(char c[], int *r){ // loop-funktion. Tager en streng og kører funktionen efter do og før loop n gange
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

void ifelse(char c[], int* right){ // conditional funktion. Tager fra første char efter if. 
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

void custom(char c[]){ // kører en custom funktion fra string_map og map
    int temp_left;
    int temp_right;
    temp_left = left;
    temp_right = right;

    char * function = get_string(&string_map, c);
    passString(function);

    left = temp_left;
    right = temp_right;
}

// void test(char c[]){
//     element list[MAXSIZESTACK] = splitString(c); 
// }

// void handleList(element list[]){
//     int i = 0;
//     while (list[i].s[0] != '\\'){
//         if (list[i].s[0] == '\000'){ // then we have a digit
//             push(list[i].val);
//         }
//         else{
//             char c[MAXSIZESTACK] = list[i].s;
//             void (*fptr)();
//             fptr = get(&map, list[i].s);

//             // jeg skal bare sende en pointer med til hvilken funktion vi er ved og så er det det samme


//             if (fptr == &define){
//                 fptr(c, &right, &left); // we need to define a function and update indexes after
//                 continue;
//             }

//             else if (fptr == &printString){
//                 fptr(c, &right, &left); // we need to parse the funktion and the pointers
//                 continue;
//             }

//             else if (fptr == &custom){
//                 fptr(curr_str);
//             }

//             else if (fptr == &ifelse){
//                 fptr(c, &right);
//             }

//             else if (fptr == &loop){
//                 fptr(c, &right);
//             }

//             else if (fptr == &i_counter){
//                 push(loop_counter);
//             }

//             else if (fptr != NULL){
//                 fptr();
//             }
//             else{
//                 printf("\033[1;31m"); // source for color-code and how to : https://medium.com/@selvarajk/adding-color-to-your-output-from-c-58f1a4dc4e75
//                 printf("%s - ?\n", curr_str); 
//                 printf("\033[0m");
//                 // printf("Letter is %c", c[right]);
//                 return;
//             }

//         }
//     }
// }

element * splitString(char c[]){
    left = 0;
    right = 0;
    int curr = 0;
    int function_counter = 0;

    element * list = (element *) calloc(MAXSIZESTACK, sizeof(element));
    for (; right<strlen(c); right++){ // kør så længe der er char i strengen
        if (c[right] == ' '){ // hvis et mellemrum findes
            if (isdigit(c[left]) != 0){ // og det er et digit
                for(int i=0; i<right-left; i++){ // kør fra left til right og læg dem til med den rigtige potens
                    curr += (int)(c[left+i]-'0') * pow(10, right-left-1-i); // lægger tallet på left til ganget med en potens af 10
                }
                list[function_counter].val = curr;
                list[function_counter++].s[0] = '\000';
                curr = 0; // reset curr til næste gang et digit findes
            }
            else{
                strncpy(list[function_counter].s, c+left, right-left); // pas på med den her igen:) - overvej loop
                list[function_counter++].s[right-left] = '\\';
            }
        }
    }

    list[function_counter].s[0] == '\000';

    return list;
}


void passString(char c[]){ // deler strengen op i dele og pusher digits og kører funktioner
    left = 0;
    right = 0;
    int curr = 0;
    char curr_str[MAXSIZESTACK];

    element * list = splitString(c);
    
    int i=0;
    while (list[i].s[0] != '\\'){
        if (list[i].s[0] == '\000'){ // then we have a digit
            printf("%d", list[i].val);
        }
        else{
            printf("%s", list[i].s);
        }
        i++;
    }

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

void define(char c[], int* right, int* left){ // definerer en ny custom funktion
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
