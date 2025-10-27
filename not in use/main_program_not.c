#include "stack_implementation.h"
#define MAX_INPUT_LENGTH 50
#include <string.h>

int main(){
    stack s = init_stack();
    char input[MAX_INPUT_LENGTH];
    char check[] = "quit";
    char substring[MAX_INPUT_LENGTH];


    bool flag = true;

    while(flag){
        fgets(input, MAX_INPUT_LENGTH, stdin); // takes string of length x

        int left;
        int right;

        /*
        4 cases: 
            char is space
                hvis current er digit append til stack
                hvis current er alpha kør funktion

            char is digit
                gem og fortsæt til næste index


            char is alpha
                gem og fortsæt til næste index

            char is newline 
                end program
        
        
        */

        // for (int i=0; i<MAX_INPUT_LENGTH; i++){
            // if (isdigit(input[i])){

        //     }
        // }
        

    }
    for (int i=0;i<5;i++){
        node * n = make_test_node(i);
        append_stack(&s, n);
    }


}