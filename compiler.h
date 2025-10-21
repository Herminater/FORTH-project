#include "stackArray.h"
#include "hashMapArray.h"

#define MAXSIZE_HASHMAP 200
typedef struct Interpretor{
    HashMapArray * array_of_funcs;
    HashMapArray * array_of_custom_funcs;
    HashMapArray * variable_store;
    Stack * stack;
}Interpretor;

Interpretor * init_interpretor(){
    Interpretor * interpretor = (Interpretor *) malloc(sizeof(Interpretor));
    interpretor->array_of_funcs = init_hashMapArray(type_func, MAXSIZE_HASHMAP);
    interpretor->array_of_custom_funcs = init_hashMapArray(type_functions_liste_element, MAXSIZE_HASHMAP);
    interpretor->variable_store = init_hashMapArray(pointer_to_int, MAXSIZE_HASHMAP);
    interpretor->stack = init_stack();
    
    return interpretor;
};
