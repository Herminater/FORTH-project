#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

// generic array med put og get function

typedef struct functions_liste_element{
    int type;
    int val;
    char s[200];
    int * pointer;
}functions_liste_element;
typedef struct element{
    char * key;
    union value * val;
} element;
union value{
    int i;
    char * s;
    void (*fptr)();
    functions_liste_element * element_liste;
    int * pointer_to_int;

} value;

enum type_of_value{
        type_int,
        type_str,
        type_func,
        type_functions_liste_element,
        pointer_to_int
};

typedef struct{
    int type;
    element * list;
    int listEnd;
} HashMapArray;


union value * init_value_func(void(*fptr)()){
    union value * ny_v = (union value * ) malloc(sizeof(ny_v));
    ny_v->fptr = fptr;
    return ny_v;
}

union value * init_value_pointer(int * pointer){
    union value * ny_v = (union value *) malloc(sizeof(value));
    ny_v->pointer_to_int = pointer;
    return ny_v;
}

element * init_element(char k[], union value v){
    element * elm = (element * )malloc(sizeof(element));
    union value * ny_v = (union value *)malloc(sizeof(union value));
    *ny_v = v; 
    elm->key = k;
    elm->val = ny_v;
    return elm;
}

HashMapArray * init_hashMapArray(int t, int size){
    HashMapArray * hashmaparray = (HashMapArray * )malloc(sizeof(HashMapArray));
    hashmaparray->type = t;
    hashmaparray->list = (element * )malloc(sizeof(element) * size);
    hashmaparray->listEnd = 0;
    return hashmaparray;
}

void put(HashMapArray * hashmaparray, char k[], union value *val, int type){
    if (hashmaparray->type != type){
        printf("Error, typees dont match");
        return;
    }
    
    element * ny_elm = ny_elm = init_element(k, *val);
    element * v = (element *) malloc(sizeof(element));

    for (int i=0; i<hashmaparray->listEnd; i++){
        *v = hashmaparray->list[i];
        if (strcmp(v->key, k)==0){
            hashmaparray->list[i] = *ny_elm;
            return;
        }
    }
    // eksisterer ikke endnu
    hashmaparray->list[hashmaparray->listEnd] = *ny_elm;
    hashmaparray->listEnd += 1;
}   

// liste af elementer
void put_elements(HashMapArray * hashmaparray, char k[], functions_liste_element e[], int type){
    union value * ny = (union value *)malloc(sizeof(union value));
    ny->element_liste = e;
    put(hashmaparray, k, ny, type);
}
// function pointer
void put_func(HashMapArray * hashmaparray, char k[], void(*fptr)(), int type){
    union value * ny = (union value *)malloc(sizeof(union value));
    ny->fptr = fptr;
    put(hashmaparray, k, ny, type);
}

union value * get(HashMapArray * hashmaparray, char k[]){
    element * v = (element *) malloc(sizeof(element));
    
    for (int i=0; i<hashmaparray->listEnd; i++){
        *v = hashmaparray->list[i];
        if (strcmp(v->key, k) == 0){
            return v->val;
        }
    }
    printf("Value not found");
    return NULL;
}

// void dummy1(){};
// void dummy2(){};
// void dummy4(){};


// int main(){
    
//     HashMapArray * hsh_int = init_hashMapArray(type_int, 10);
//     HashMapArray * hsh_string = init_hashMapArray(type_str, 10);
//     HashMapArray * hsh_func = init_hashMapArray(type_func, 10);

//     union value v;
//     v.i = 1;
//     put(hsh_int, "en", v, type_int);
//     v.i = 2;
//     put(hsh_int, "to", v, type_int);
//     v.i = 4;
//     put(hsh_int, "en", v, type_int);

//     v.s = "test";
//     put(hsh_string, "en", v, type_str);
//     v.s = "test2";
//     put(hsh_string, "to", v, type_str);
//     v.s = "test4";
//     put(hsh_string, "en", v, type_str);

//     v.fptr = &dummy1;
//     put(hsh_func, "en", v, type_func);
//     v.fptr = &dummy2;
//     put(hsh_func, "to", v, type_func);
//     v.fptr = &dummy4;
//     put(hsh_func, "en", v, type_func);


//     void (*fptr)() = (get(hsh_func, "en"))->fptr;
//     printf("S");
// }