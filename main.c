#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>
#include <math.h>
#include <string.h>
#include "interpretor.h"

/*
BUGS:

TODO:
Fikse så loop ikke har en global variabel 

IN THE WORKS:

*/


int main(void){
    // Indeholder hashmap til basic funcs, hashmap til custom funcs og stacken
    Interpretor * interpretor = init_interpretor();

    char c[MAXSIZE_CHAR]; // holder nuværende input fra brugeren
    int str_length;

    while (true){
        fgets(c, MAXSIZE_CHAR, stdin);
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
        handleList(interpretor->variable_store, interpretor->default_func_store, interpretor->custom_func_store, interpretor->stack, list, 0, BIGNUM);
        printStack(interpretor->stack);
    }

    return 1;
}
