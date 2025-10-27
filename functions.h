#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>
#include <math.h>
#include <string.h>


/*
BUGS:

TODO:
Fikse så loop ikke har en global variabel 

lige nu opfører en variable sig som et defineret ord og retunerer værdien ved bare at skrive navnet.
Den siger at den gemmer på memory adress 1000 og derfor starter med dette tal, men hvordan gøres det i c? 

IN THE WORKS:


*/
#define MAXSIZE_CHAR 200
#define MAXSIZE_STACK 200
#define BIGNUM 5000

// this is for testing the elements in the function list
enum type_of_element{
    string, 
    digit, 
    stop,
    pointer
};

int loop_counter; // loop-counter til loops

// setup

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
void CR(Stack * stck){ // linjeskift
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
void store(Stack * stck){ // ! 
    int *adress = (void *) pop(stck);
    int value = pop(stck);
    *adress = value;
    return;
}
void show(Stack * stck){
    int *adress = (void *) pop(stck);
    push(stck, *adress);

}
// prototyper
void define(HashMapArray * default_func_store, HashMapArray * custom_func_store, functions_liste_element list[], int *i);
void handleList(HashMapArray * variable_store, HashMapArray * default_func_store, HashMapArray * custom_func_store, Stack * stck, functions_liste_element list[], int start, int last);
void variable(HashMapArray * variable_store, HashMapArray * default_func_store, HashMapArray * custom_func_store, functions_liste_element list[], int * i);
void custom_variable(HashMapArray * variable_store, HashMapArray * default_func_store, HashMapArray * custom_func_store, Stack * stck, char k[], int * i);

// mere kompliserede funktioner
void printString(functions_liste_element list[], int * i){ 

    *i += 1; // skip ."
    int str_length;
    while (list[*i].type != stop){
        if (list[*i].type == digit){
            printf("%d", list[*i].val);
        }
        else{
            // vi har en streng
            str_length = strlen(list[*i].s);

            for (int j = 0; j<str_length; j++){
                if (list[*i].s[j] == '\"'){
                    return;
                };
                printf("%c", list[*i].s[j]);
            }
        }         
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
void loop(HashMapArray * variable_store,HashMapArray * default_func_store, HashMapArray * custom_func_store, Stack * stck, functions_liste_element list[], int * i){ // loop-funktion. Tager en streng og kører funktionen efter do og før loop n gange
    *i += 1; // hop over do
    int loop = find_subString(list, "loop", *i);
    int start = pop(stck);
    int end = pop(stck);

    loop_counter = start; 
    for (int k=start;k<end;k++){
        handleList(variable_store,default_func_store, custom_func_store, stck, list, *i, loop);
        loop_counter++;
    }
    *i = loop;
}
void ifelse(HashMapArray * variable_store, HashMapArray * default_func_store, HashMapArray * custom_func_store, Stack * stck, functions_liste_element list[], int * i){ // conditional funktion. Tager fra første char efter if. 
    *i += 1;

    int p = pop(stck);
    bool condition = (p == 0) ? false : true;
    char new[MAXSIZE_CHAR];

    int idx_then = find_subString(list, "then", *i);
    int idx_else = find_subString(list, "else" ,*i);
    
    if (idx_then == -1){
        printf("ERROR");
    }
    int idx_før = *i;
    // hvis ikke t -> find else

    if (!condition){ // hvis condition ikke er true skal der kun gøres noget hvis der er en else
        if (idx_else != -1){
            handleList(variable_store, default_func_store, custom_func_store, stck, list, idx_else+1, idx_then);
        }
    }else{
        if (idx_else != -1){
            handleList(variable_store,default_func_store, custom_func_store, stck, list, *i, idx_else);
        }
        else{
            handleList(variable_store,default_func_store, custom_func_store, stck, list, *i, idx_then);
        }
    }
    *i = idx_then;// skip then
}
void custom(HashMapArray * variable_store, HashMapArray * default_func_store, HashMapArray * custom_func_store, Stack * stck, char k[], int * i){ // kører en custom funktion fra string_map og map

    int curr_idx = *i; // vi vil ikke ændre i

    // FEJLEN LIGGER HER, da funtionen bliver et enkelt element istedet for en liste af elementer...
    functions_liste_element * function = (get(custom_func_store, k)->element_liste);
    handleList(variable_store ,default_func_store, custom_func_store, stck, function, 0, BIGNUM);

    *i = curr_idx;
}
void handleList(HashMapArray * variable_store, HashMapArray * default_func_store, HashMapArray * custom_func_store, Stack * stck, functions_liste_element * list, int first, int last){
    
    
    
    void (*fptr)();
    int i=first;
    union value * temp;
    while (list[i].type != stop && i < last){
        // vi har et digit
        if (list[i].type == digit){ 
            push(stck, list[i].val);
        }
        // vi har en funktion
        else if (list[i].type == pointer_to_int){
            push(stck, (int)&(list[i].pointer));
        }
        else{
            temp = get(default_func_store, list[i].s);
            if (temp != NULL){
                fptr = temp->fptr;
            }

            if (temp == NULL){
                printf("\033[1;31m"); // source for color-code and how to : https://medium.com/@selvarajk/adding-color-to-your-output-from-c-58f1a4dc4e75
                printf("%s - ?\n", list[i].s); 
                // printf("error");
                printf("\033[0m");
                // printf("Letter is %c", c[right]);
                return;
            }
            
            else if (fptr == &define){
                fptr(default_func_store, custom_func_store, list, &i); // we need to define a function and update indexes after
            }

            else if (fptr == &printString){
                fptr(list, &i); // we need to parse the funktion and the pointers
            }

            else if (fptr == &custom){
                fptr(variable_store, default_func_store, custom_func_store, stck, list[i].s, &i);
            }

            else if (fptr == &ifelse){
                fptr(variable_store, default_func_store, custom_func_store, stck, list, &i);
            }
            else if (fptr == &loop){
                fptr(variable_store, default_func_store, custom_func_store, stck, list, &i);
            }

            else if (fptr == &i_counter){
                i_counter(stck);
            }

            else if (fptr == &variable){
                variable(variable_store, default_func_store, custom_func_store, list, &i);
            }

            else if (fptr == &custom_variable){
                custom_variable(variable_store, default_func_store, custom_func_store, stck, list[i].s, &i);
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

    functions_liste_element * list = malloc(sizeof(functions_liste_element)*MAXSIZE_STACK);

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
void define(HashMapArray * default_func_store, HashMapArray * custom_func_store, functions_liste_element list[], int * i){ // definerer en ny custom funktion
    
    functions_liste_element * ny_list = malloc(sizeof(functions_liste_element)*MAXSIZE_STACK);

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
    put_elements(custom_func_store, list[first_idx-1].s, ny_list, type_functions_liste_element);
    put_func(default_func_store, list[first_idx-1].s, &custom, type_func); 
}   
void custom_variable(HashMapArray * variable_store, HashMapArray * default_func_store, HashMapArray * custom_func_store, Stack * stck, char k[], int * i){
    int curr_idx = *i;
    functions_liste_element * function = (get(variable_store, k)->element_liste);
    handleList(variable_store ,default_func_store, custom_func_store, stck, function, 0, BIGNUM);
    *i = curr_idx;
}
void variable(HashMapArray * variable_store, HashMapArray * default_func_store, HashMapArray * custom_func_store, functions_liste_element list[], int * i){
    *i += 1; // variable keyword

    int * temp = (int*)malloc(sizeof(int));
    *temp = 1001;
    // den gemte værdi skal gøres til en pointer, så den opdateres også når man opdaterer direkte fra
    functions_liste_element * ny_list = malloc(sizeof(functions_liste_element)*MAXSIZE_STACK);
    ny_list[0].type = pointer_to_int;
    ny_list[0].pointer = temp;
    ny_list[1].type = stop;

    put_elements(variable_store, list[*i].s, ny_list, pointer_to_int);
    put_func(default_func_store, list[*i].s, &custom_variable, type_func); 

}
