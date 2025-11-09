#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>
#include <math.h>
#include <string.h>
#include "functions.h"

/*
BUGS:
None?

TODO:
Implementere +loop og -loop
implementere XX (skal slette alt i alle maps osv) -> kræver clear-func i hashmaps og stack osv. 
tests 
omvendt test generering 


*/



int main(void){
    // Indeholder hashmap til basic funcs, hashmap til custom funcs og stacken
    Interpretor * interpretor = init_interpretor();
    create_basic_funcs(interpretor);

    char c[MAXSIZE_CHAR]; // holder nuværende input fra brugeren
    int str_length;
    bool flag = true; // nu kører den kun en gang

    FILE * fptr;
    fptr = fopen("input.txt", "r");



    while (flag){
        // fgets(c, MAXSIZE_CHAR, stdin);
        fgets(c, MAXSIZE_CHAR, fptr); // now reads from input file
        // printf("Herman %s", c);
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
        handleList(interpretor, list, 0, BIGNUM);
        printStack(interpretor->stack);

        flag = false;
    }
    fclose(fptr);
    return 1;
}
