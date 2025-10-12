#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>
#include <math.h>
#include <string.h>
#include "hashmap_implementation.h"
// #include "hashmap_implementation_string.h"
#include "hashmap_implementation_element.h"

/*
BUGS:
1 -> if 50 then -> . giver nogen gange at print ikke kører
." test" <- skal have et mellemrum efter test ellers duer det ikke.

*/

#define MAXSIZESTACK 200
#define ARRAYEND 5000

enum operator{
    string, 
    digit, 
    stop
};

int stackEnd = -1;
int stck[MAXSIZESTACK];

hashMap map; // predefined functions
hashMapElement custom_function_map; // custom function-values

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
    printf("\n");
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
void stopper(){}

void printString(element list[], int * i){  // tager en streng og printer fra venstre til højre

    *i += 1; // skip ."

    while (list[*i].type != stop){
        if (list[*i].type == digit){
            printf("%d", list[*i].val);
        }
        else{
            if (strcmp(list[*i].s, "\"") == 0){
                break;
            }
            printf("%s", list[*i].s);
        }
        printf(" ");
        *i += 1;
    }
}
void define(element list[], int *i);
void handleList(element list[], int start, int last);

void i_counter(){ // adressen bruges bare til at parse korrekt funktion.
    push(loop_counter);
}

int find_subString(element list[], char st[], int start){ // finder substring og retunerer første index, hvis substring ikke findes retuneres -1
    int j = 0; 
    while (list[start+j].type != stop){
        if (list[start+j].type == string && strcmp(list[start+j].s, st) == 0){
            return start+j;
        }
        j++;
    }
    return -1;
}

void loop(element list[], int * i){ // loop-funktion. Tager en streng og kører funktionen efter do og før loop n gange
    *i += 1; // hop over do
    int loop = find_subString(list, "loop", *i);
    int start = *pop();
    int end = *pop();

    loop_counter = start; 
    for (int k=start;k<end;k++){
        handleList(list, *i, loop);
        loop_counter++;
    }
    *i = loop;
}

void ifelse(element list[], int * i){ // conditional funktion. Tager fra første char efter if. 
    *i += 1;

    int p = *pop();
    bool condition = (p == 0) ? false : true;
    char new[MAXSIZESTACK];

    int idx_then = find_subString(list, "then", *i);
    int idx_else = find_subString(list, "else" ,*i);
    
    if (idx_then == -1){
        printf("ERROR");
    }
    int idx_før = *i;
    // hvis ikke t -> find else

    if (!condition){ // hvis condition ikke er true skal der kun gøres noget hvis der er en else
        if (idx_else != -1){
            handleList(list, idx_else+1, idx_then);
        }
    }else{
        if (idx_else != -1){
            handleList(list, *i, idx_else);
        }
        else{
            handleList(list, *i, idx_then);
        }
    }
    *i = idx_then;// skip then
}

void custom(char k[], int * i){ // kører en custom funktion fra string_map og map

    int curr_idx = *i; // vi vil ikke ændre i

    element * function = get_element(&custom_function_map, k);
    handleList(function, 0, ARRAYEND);

    *i = curr_idx;
}

void handleList(element list[], int first, int last){
    void (*fptr)();
    int i=first;

    while (list[i].type != stop && i < last){
        // vi har et digit
        if (list[i].type == digit){ 
            push(list[i].val);
        }
        // vi har en funktion
        else{
            fptr = get(&map, list[i].s);
            
            if (fptr == &define){
                fptr(list, &i); // we need to define a function and update indexes after
            }

            else if (fptr == &printString){
                fptr(list, &i); // we need to parse the funktion and the pointers
            }

            else if (fptr == &custom){
                fptr(list[i].s, &i);
            }

            else if (fptr == &ifelse){
                fptr(list, &i);
            }

            else if (fptr == &loop){
                fptr(list, &i);
            }

            else if (fptr == &i_counter){
                i_counter();
            }

            else if (fptr != NULL){
                fptr();
            }
            else{
                printf("\033[1;31m"); // source for color-code and how to : https://medium.com/@selvarajk/adding-color-to-your-output-from-c-58f1a4dc4e75
                printf("%s - ?\n", list[i].s); 
                // printf("error");
                printf("\033[0m");
                // printf("Letter is %c", c[right]);
                return;
            }
            
        }
        i++;
    }
}

element * splitString(char c[]){
    int left = 0;
    int right = 0;
    int curr = 0;
    int function_counter = 0;

    element * list = malloc(sizeof(element)*MAXSIZESTACK);

    for (; right<strlen(c); right++){ // kør så længe der er char i strengen
        if (c[right] == ' '){ // hvis et mellemrum findes
            if (isdigit(c[left]) != 0){ // og det er et digit
                for(int i=0; i<right-left; i++){ // kør fra left til right og læg dem til med den rigtige potens
                    curr += (int)(c[left+i]-'0') * pow(10, right-left-1-i); // lægger tallet på left til ganget med en potens af 10
                }
                list[function_counter].val = curr;
                list[function_counter].type = digit;
                function_counter++;
                curr = 0; // reset curr til næste gang et digit findes
            }
            else{
                strncpy(list[function_counter].s, c+left, right-left); // pas på med den her igen:) - overvej loop
                list[function_counter].s[right-left] = '\000';
                list[function_counter].type = string;
                function_counter++;
            }
            left = right+1;
        }
    }

    list[function_counter].type = stop;

    return list;
}

void define(element list[], int * i){ // definerer en ny custom funktion
    
    element * ny_list = malloc(sizeof(element)*MAXSIZESTACK);

    // first one is the key;
    *i += 2; // skip the colon and the key;
    int first_idx = *i;
    int function_count = 0;

    // find semikolon;
    while (list[*i].type != stop){ // antager at der faktisk er et semikolon..
        if (list[*i].type == string ){
            if (strcmp(list[*i].s, ";") == 0){
                break; // vi har fundet et semocolon
            }

            strcpy(ny_list[(function_count)].s, list[(*i)].s);
            ny_list[function_count].type = string;

        }
        else{
            ny_list[function_count].val = list[(*i)].val;
            ny_list[function_count].type = digit;
        }
        function_count++;
        *i += 1;
    }
    ny_list[function_count].type = stop;

    // gem streng
    put_element(&custom_function_map, list[first_idx-1].s, ny_list);
    put(&map, list[first_idx-1].s, &custom); 
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
    put(&map, ";", &stopper);


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

        // deler strengen i digits og strings
        element * list = splitString(c);

        // kører respektive funktioner
        handleList(list, 0, ARRAYEND);
        
        printStack();
    }

    return 1;
}
