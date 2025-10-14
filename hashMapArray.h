#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

// generic array med put og get function

typedef struct functions_liste_element{
    int type;
    int val;
    char s[200];
}functions_liste_element;

enum type_of{
        type_int,
        type_str,
        type_func,
        type_functions_liste_element
};

union value{
    int i;
    char * s;
    void (*fptr)();
    functions_liste_element * element_liste;

} value;

typedef struct element{
    char * key;
    union value * val;
} element;

typedef struct{
    int type;
    element * list;
    int listEnd;
} HashMapArray;

// currently not being used
bool compare(element * a, union value * b, int type){
    if (type == type_int){
        return (a->val->i == b->i);
    }
    if (type == type_str){
        return (strcmp(a->val->s, b->s) == 0);
    }
    if (type = type_func){
        return (a->val->fptr == b->fptr);
    }
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

void put(HashMapArray * hashmaparray, char k[], union value val, int type){
    if (hashmaparray->type != type){
        printf("Error, typees dont match");
    }
    
    element * ny_elm = ny_elm = init_element(k, val);
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
    union value ny;
    ny.element_liste = e;
    put(hashmaparray, k, ny, type);
}
// function pointer
void put_func(HashMapArray * hashmaparray, char k[], void(*fptr)(), int type){
    union value ny;
    ny.fptr = fptr;
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