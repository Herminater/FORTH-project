#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>
#include <math.h>
#include <string.h>
#include "stackArray.h"
#include "hashMapArray.h"

/*
BUGS:
1 -> if 50 then -> . giver nogen gange at print ikke kører
." test" <- skal have et mellemrum efter test ellers duer det ikke.


TODO:
Ændre sådan at man bare bruger et compiler struct til at køre alt
Fikse så loop ikke har en global variabel 
Gøre operator til en del af alle?
Samle alle definationerne af forskellige max-værdier osv
Gør sæt mellemrum ind delen af while(true) til en function
add variable med memory (Skulle være let siden stacken har int *)

IN THE WORKS:
Ændre sådan at alle navnene på hashmaps, funktioner osv passer

*/

#define MAXSIZESTACK 200
#define ARRAYEND 5000

enum operator{
    string, 
    digit, 
    stop
};

int loop_counter; // loop-counter til loops

void mult(Stack * stck){ // popper 2 værdier fra stacken og pusher produktet
    if (stck->stackEnd > 0){
        int a = pop(stck);
        int b = pop(stck);
        push(stck, a * b);
    }
    else{
        printf("Not enough items in stack");
    }
}
void add(Stack * stck){ // popper 2 værdier fra stacken og pusher summen
    if (stck->stackEnd > 0){
        int a = pop(stck);
        int b = pop(stck);
        push(stck, a + b);
    }
    else{
        printf("Not enough items in stack");

    }
}
void sub(Stack * stck){ // popper 2 værdier fra stacken og pusher differencen
    if (stck->stackEnd > 0){
        int a = pop(stck);
        int b = pop(stck);
        push(stck, b - a);
    }
    else{
        printf("Not enough items in stack");
    }
}
void divid(Stack * stck){ // popper 2 værdier fra stacken og pusher de to tal divideret
    if (stck->stackEnd > 0){
        int a = pop(stck);
        int b = pop(stck);
        push(stck, b / a);
    }
    else{
        printf("Not enough items in stack");
    }
}
void mod(Stack * stck){ // popper 2 værdier fra stacken og pusher moduluproduktet
    if (stck->stackEnd > 0){
        int a = pop(stck);
        int b = pop(stck);
        push(stck, b % a);
    }
    else{
        printf("Not enough items in stack");
    }
}
void equals(Stack * stck){ // popper 2 værdier fra stacken og pusher om de er ens
    if (stck->stackEnd > 0){
        int a = pop(stck);
        int b = pop(stck);
        push(stck, b == a);
    }
    else{
        printf("Not enough items in stack");
    }
}
void less(Stack * stck){ // > popper 2 værdier fra stacken og pusher om toppen af stacken er mindre end anden øverst
    if (stck->stackEnd > 0){
        int a = pop(stck);
        int b = pop(stck);
        push(stck, a < b);
    }
    else{
        printf("Not enough items in stack");
    }
}
void more(Stack * stck){ // < popper 2 værdier fra stacken og pusher om toppen af stacken er større end anden øverst
    if (stck->stackEnd > 0){
        int a = pop(stck);
        int b = pop(stck);
        push(stck, b < a);
    }
    else{
        printf("Not enough items in stack");
    }
}
void AND(Stack * stck){ // popper 2 værdier fra stacken og pusher om de er ens
    if (stck->stackEnd > 0){
        int a = pop(stck);
        int b = pop(stck);
        push(stck, a && b);
    }
    else{
        printf("Not enough items in stack");
    }
}
void OR(Stack * stck){ // popper 2 værdier fra stacken og pusher om en af de er sande
    if (stck->stackEnd > 0){
        int a = pop(stck);
        int b = pop(stck);
        push(stck, a || b);
    }
    else{
        printf("Not enough items in stack");
    }
}
void INVERT(Stack * stck){ // pusher modsat boolean value af topværdien
    if (!is_empty(stck)){
        int a = pop(stck);
        push(stck, !a);
    }
    else{
        printf("Not enough items in stack");
    }
}
void print(Stack * stck){ // .  popper og printer
    if (!is_empty(stck)){
        int a = pop(stck);
        printf("%d ", a);
    }
    else{
        printf("Not enough items in stack");
    }
}
void EMIT(Stack * stck){ // int as ascii.  popper og printer som ascii
    if (!is_empty(stck)){
        int a = pop(stck);
        printf("%c ", (char)a);
    }
    else{
        printf("Not enough items in stack");
    }
}
void CR(){ // linjeskift
    printf("\n");
}
void dup(Stack * stck){ // duplikerer top-værdien
    if (!is_empty(stck)){
        int a = pop(stck);
        push(stck, a);
        push(stck, a);
    }
    else{
        printf("Not enough items in stack");
    }
}
void drop(Stack * stck){ // popper topværdien
    if (!is_empty(stck)){
        pop(stck);
    }
    else{
        printf("Not enough items in stack");
    }
}
void swap(Stack * stck){ // swapper de to øverste
    if (stck->stackEnd > 0){
        int a = pop(stck);
        int b = pop(stck);
        push(stck, a);
        push(stck, b);
    }
    else{
        printf("Not enough items in stack");
    }
}
void over(Stack * stck){ // tager anden øverste og dupper og pusher den
   if (stck->stackEnd > 0){
        int a = pop(stck);
        int b = pop(stck);
        push(stck, a);
        push(stck, b);
        push(stck, a);

    }
    else{
        printf("Not enough items in stack");
    }
}
void rotate(Stack * stck){ // roterer øverste tre værdier
    if (stck->stackEnd > 1){
        int a = pop(stck);
        int b = pop(stck);
        int c = pop(stck);
        push(stck, b);
        push(stck, c);
        push(stck, a);
    }
    else{
        printf("Not enough items in stack");
    }
};

// prototyper
void define(HashMapArray * hsh_func, HashMapArray * custom_function_map, functions_liste_element list[], int *i);
void handleList(HashMapArray * hsh_func, HashMapArray * custom_function_map, Stack * stck, functions_liste_element list[], int start, int last);

void printString(functions_liste_element list[], int * i){ 

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
void i_counter(Stack * stck){ // adressen bruges bare til at parse korrekt funktion.
    push(stck, loop_counter);
}
int find_subString(functions_liste_element list[], char st[], int start){ // finder substring og retunerer første index, hvis substring ikke findes retuneres -1
    int j = 0; 
    while (list[start+j].type != stop){
        if (list[start+j].type == string && strcmp(list[start+j].s, st) == 0){
            return start+j;
        }
        j++;
    }
    return -1;
}
void loop(HashMapArray * hsh_func, HashMapArray * custom_function_map, Stack * stck, functions_liste_element list[], int * i){ // loop-funktion. Tager en streng og kører funktionen efter do og før loop n gange
    *i += 1; // hop over do
    int loop = find_subString(list, "loop", *i);
    int start = pop(stck);
    int end = pop(stck);

    loop_counter = start; 
    for (int k=start;k<end;k++){
        handleList(hsh_func, custom_function_map, stck, list, *i, loop);
        loop_counter++;
    }
    *i = loop;
}
void ifelse(HashMapArray * hsh_func, HashMapArray * custom_function_map, Stack * stck, functions_liste_element list[], int * i){ // conditional funktion. Tager fra første char efter if. 
    *i += 1;

    int p = pop(stck);
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
            handleList(hsh_func, custom_function_map, stck, list, idx_else+1, idx_then);
        }
    }else{
        if (idx_else != -1){
            handleList(hsh_func, custom_function_map, stck, list, *i, idx_else);
        }
        else{
            handleList(hsh_func, custom_function_map, stck, list, *i, idx_then);
        }
    }
    *i = idx_then;// skip then
}
void custom(HashMapArray * hsh_func, HashMapArray * custom_function_map, Stack * stck, char k[], int * i){ // kører en custom funktion fra string_map og map

    int curr_idx = *i; // vi vil ikke ændre i

    functions_liste_element * function = (get(custom_function_map, k)->element_liste);
    handleList(hsh_func, custom_function_map, stck, function, 0, ARRAYEND);

    *i = curr_idx;
}
void handleList(HashMapArray * hsh_func, HashMapArray * custom_function_map, Stack * stck, functions_liste_element list[], int first, int last){
    void (*fptr)();
    int i=first;

    while (list[i].type != stop && i < last){
        // vi har et digit
        if (list[i].type == digit){ 
            push(stck, list[i].val);
        }
        // vi har en funktion
        else{
            fptr = (get(hsh_func, list[i].s)->fptr);
            
            if (fptr == &define){
                fptr(hsh_func, custom_function_map, list, &i); // we need to define a function and update indexes after
            }

            else if (fptr == &printString){
                fptr(list, &i); // we need to parse the funktion and the pointers
            }

            else if (fptr == &custom){
                fptr(hsh_func, custom_function_map, stck,list[i].s, &i);
            }

            else if (fptr == &ifelse){
                fptr(hsh_func, custom_function_map, stck, list, &i);
            }
            else if (fptr == &loop){
                fptr(hsh_func, custom_function_map, stck, list, &i);
            }

            else if (fptr == &i_counter){
                i_counter(stck);
            }

            else if (fptr != NULL){
                fptr(stck);
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
functions_liste_element * splitString(char c[]){
    int left = 0;
    int right = 0;
    int curr = 0;
    int function_counter = 0;

    functions_liste_element * list = malloc(sizeof(functions_liste_element)*MAXSIZESTACK);

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
void define(HashMapArray * hsh_func, HashMapArray * custom_function_map, functions_liste_element list[], int * i){ // definerer en ny custom funktion
    
    functions_liste_element * ny_list = malloc(sizeof(functions_liste_element)*MAXSIZESTACK);

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
    put_elements(custom_function_map, list[first_idx-1].s, ny_list, type_functions_liste_element);
    put_func(hsh_func, list[first_idx-1].s, &custom, type_func); 
}   

int main(void){
    HashMapArray * hsh_func = init_hashMapArray(type_func, 10);
    HashMapArray * custom_function_map = init_hashMapArray(type_functions_liste_element, 10);
    Stack * stack = init_stack();

    // definer basic functions

    put(hsh_func, "*", (union value)&mult, type_func); 
    put(hsh_func, "/", (union value)&divid, type_func);
    put(hsh_func, "+", (union value)&add, type_func);
    put(hsh_func, "-", (union value)&sub, type_func);
    put(hsh_func, "mod", (union value)&mod,type_func );
    put(hsh_func, "=", (union value)&equals,type_func );
    put(hsh_func, ">", (union value)&less,type_func );
    put(hsh_func, "<", (union value)&more,type_func );
    put(hsh_func, "and", (union value)&AND,type_func );
    put(hsh_func, "or", (union value)&OR,type_func );
    put(hsh_func, "invert", (union value)&INVERT,type_func );
    put(hsh_func, ".", (union value)&print,type_func);
    put(hsh_func, "emit", (union value)&EMIT,type_func );
    put(hsh_func, "cr", (union value)&CR,type_func);
    put(hsh_func, "dup", (union value)&dup,type_func);
    put(hsh_func, "drop", (union value)&drop,type_func);
    put(hsh_func, "swap", (union value)&swap,type_func);
    put(hsh_func, "over", (union value)&over,type_func);
    put(hsh_func, "rot", (union value)&rotate,type_func);
    put(hsh_func, ":", (union value)&define, type_func);
    put(hsh_func, ".\"", (union value)&printString,type_func);
    put(hsh_func, "if", (union value)&ifelse,type_func);
    put(hsh_func, "do", (union value)&loop,type_func);
    put(hsh_func, "i", (union value)&i_counter,type_func);
    
    char c[MAXSIZESTACK]; // holder nuværende input fra brugeren
    int str_length;

    while (true){
        fgets(c, MAXSIZESTACK, stdin);
        str_length = strlen(c);

        if (strcmp(c, "quit") == 0){ // quit-funktion
            break;
        }

        if (c[str_length-2] != ' '){ // sørger for mellemrum til sidst hvis glemt
            c[str_length-1] = ' ';
            c[str_length]= '\n';
            c[str_length+1] = '\000';
        }

       
        // deler strengen i digits og strings
        functions_liste_element * list = splitString(c);
        // kører respektive funktioner
        handleList(hsh_func, custom_function_map, stack, list, 0, ARRAYEND);
        printStack(stack);
    }

    return 1;
}
