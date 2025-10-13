#include "stackArray.h"
#include "hashmap_implementation_element.h"
#include "hashmap_implementation_functions.h" // funktioner som values

typedef struct Interpretor{
    hashMap * hashMapFunction;
    hashMapElement * hashMapElement;
    Stack * stck;
};

Interpretor * init_interpretor(){
    Interpretor * interpretor = (Interpretor *) malloc(sizeof(Interpretor));
    interpretor->hashMapFunction = &(init_hashMap());
    interpretor->hashMapElement = &(init_hashMap_element());
    interpretor->stck = init_stack();
};
