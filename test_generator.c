
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "hashMapArray.h"

#define MAX_STRING_LEN 1000

typedef struct node{
    char * val;
    struct node * next;
} node;

typedef struct linked_list{
    node first;
    node last;
} linked_list;



node * generate_test(int length){
    node * last = ( node *)  malloc(sizeof(node));
    last->val = "";

    node * ref = last;

    node * ny;

    char * lib_remove2 = {"/ ", "* ", "+ ", "- ", "mod ", "= ", "> ", "< ", "and ",
         "or ", "invert", ". ", "emit ", "cr ", "dup ", "drop ", "swap ", "over ", "rot ", ": "};


        // TODO find længde af lib sådan det kan sendes dynamisk til løkken senere... 
    // int lib_length = sizeof(lib_remove)/sizeof(a[0]);



    // get a random number
    srand(time(NULL));   // Initialization, should only be called once. / fra github
    int r = rand(); 
    int random_num;


    // make i a number of functions
    for (int i = 0; i<length; i++){
        ny = ( node *)  malloc(sizeof(node));
        random_num = rand() % 3;

        if (random_num == 0){
            itoa(rand()%, ny->val )
        }






        ny->val = ;
        ny->next = NULL;

        last->next = ny;
        last = ny;

    }


    return ref;
}



char * ll_to_string(node * head){
    // lav plads på run-stack
    char * res = (char *)malloc(sizeof(char)*MAX_STRING_LEN);

    // tøm for garbage
    strcpy(res, "");
   
    while (head!=NULL){
        strcat(res, head->val);
        head = head->next;
    }

    return res;
}