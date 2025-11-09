#include "stackArray.h"
#include "hashMapArray.h"


#define MAXSIZE_HASHMAP 200

typedef struct Interpretor{
    HashMapArray * default_func_store;
    HashMapArray * custom_func_store;
    HashMapArray * variable_store;
    Stack * stack;
    Stack * iterator_stack;
}Interpretor;


Interpretor * init_interpretor(){
    Interpretor * interpretor = (Interpretor *) malloc(sizeof(Interpretor));
    interpretor->default_func_store = init_hashMapArray(type_func, MAXSIZE_HASHMAP);
    interpretor->custom_func_store = init_hashMapArray(type_functions_liste_element, MAXSIZE_HASHMAP);
    interpretor->variable_store = init_hashMapArray(pointer_to_int, MAXSIZE_HASHMAP);
    interpretor->stack = init_stack();
    interpretor->iterator_stack = init_stack();
    
    return interpretor;
};


