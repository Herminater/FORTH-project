#include "stackArray.h"
#include "hashMapArray.h"
#include "functions.h"


#define MAXSIZE_HASHMAP 200

typedef struct Interpretor{
    HashMapArray * default_func_store;
    HashMapArray * custom_func_store;
    HashMapArray * variable_store;
    Stack * stack;
    Stack * iterator_stack;
}Interpretor;

void create_basic_funcs(Interpretor * interpretor){
    put(interpretor->default_func_store, "/", init_value_func(&divid), type_func);
    put(interpretor->default_func_store, "*", init_value_func(&mult), type_func); 
    put(interpretor->default_func_store, "+", init_value_func(&add), type_func);
    put(interpretor->default_func_store, "-", init_value_func(&sub), type_func);
    put(interpretor->default_func_store, "mod", init_value_func(&mod),type_func );
    put(interpretor->default_func_store, "=", init_value_func(&equals),type_func );
    put(interpretor->default_func_store, ">", init_value_func(&less),type_func );
    put(interpretor->default_func_store, "<", init_value_func(&more),type_func );
    put(interpretor->default_func_store, "and", init_value_func(&AND),type_func );
    put(interpretor->default_func_store, "or", init_value_func(&OR),type_func );
    put(interpretor->default_func_store, "invert", init_value_func(&INVERT),type_func );
    put(interpretor->default_func_store, ".", init_value_func(&print),type_func);
    put(interpretor->default_func_store, "emit", init_value_func(&EMIT),type_func );
    put(interpretor->default_func_store, "cr", init_value_func(&CR), type_func); 
    put(interpretor->default_func_store, "dup", init_value_func(&dup),type_func);
    put(interpretor->default_func_store, "drop", init_value_func(&drop),type_func);
    put(interpretor->default_func_store, "swap", init_value_func(&swap),type_func);
    put(interpretor->default_func_store, "over", init_value_func(&over),type_func);
    put(interpretor->default_func_store, "rot", init_value_func(&rotate),type_func);
    put(interpretor->default_func_store, ":", init_value_func(&define), type_func);
    put(interpretor->default_func_store, ".\"", init_value_func(&printString),type_func);
    put(interpretor->default_func_store, "if", init_value_func(&ifelse),type_func);
    put(interpretor->default_func_store, "do", init_value_func(&loop),type_func);
    put(interpretor->default_func_store, "i", init_value_func(&i_counter),type_func);
    put(interpretor->default_func_store, "variable", init_value_func(&variable),type_func);
    put(interpretor->default_func_store, "!", init_value_func(&store), type_func);
    put(interpretor->default_func_store, "@", init_value_func(&show), type_func);
}

Interpretor * init_interpretor(){
    Interpretor * interpretor = (Interpretor *) malloc(sizeof(Interpretor));
    interpretor->default_func_store = init_hashMapArray(type_func, MAXSIZE_HASHMAP);
    interpretor->custom_func_store = init_hashMapArray(type_functions_liste_element, MAXSIZE_HASHMAP);
    interpretor->variable_store = init_hashMapArray(pointer_to_int, MAXSIZE_HASHMAP);
    interpretor->stack = init_stack();
    interpretor->iterator_stack = init_stack();
    create_basic_funcs(interpretor);
    
    return interpretor;
};
