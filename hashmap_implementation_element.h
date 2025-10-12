#include <string.h>
#include <stdlib.h>
#include <stdio.h>


#define HASH_LENGTH 200
#define KEY_MAX_LENGTH 200

/*
Functions:
    generate_hash(char key) -> int
    init_bucket(int hsh, char k[], int value) -> bucket * 
    init_hashMap() -> hashMap
    put(hashMap *map, char key[], int val) -> void
    get(hashMap *map, char key[]) -> int

Structures:
    bucket(hash, key, value)
    hashMap()
*/
typedef struct element{
    int type;
    int val;
    char s[200];
} element;


typedef struct bucket_element{
    int hash;
    char *key;
    element * value;
    struct bucket_element * next;
} bucket_element;

typedef struct hashMapElement{
    bucket_element * b[HASH_LENGTH];
} hashMapElement;

// generates hashvalue and assigns index within max_length of the hash map
int generate_hash_string(char key[]){
    int first = (int)key[0]*100;
    int second = (int)key[1]*1000;
    int hash = (first+second)%(HASH_LENGTH-1);
    return hash;
}

// creates a new bucket for the hashmap
bucket_element * init_bucket_element(int hsh, char k[], element val[]){ 
    bucket_element *bu = (bucket_element *) malloc(sizeof(bucket_element));
    bu->hash = hsh;
    bu->key = k;
    bu->value = val;
    bu->next = NULL;
    return bu;
}

// initializes an empty hashmap with size hash_length
hashMapElement init_hashMap_element(){
    struct hashMapElement map;
    for (int i=0; i<HASH_LENGTH; i++){
        map.b[i] = NULL;
    }
    return map;

}

// inserts key,value pair into hashmap
void put_element(hashMapElement *map, char key[], element v[]){
    int hash = generate_hash_string(key);

    // check for colisions
    // if no collisions:
    if (map->b[hash] == NULL){
        map->b[hash] = init_bucket_element(hash, key, v);
        
    }
    // if colission
    else{
        struct bucket_element * curr = map->b[hash];
        do{ 
            // if value allready present:
            if (strcmp(key, curr->key) == 0){ 
                curr->value = v;
                // memcpy(curr->value, v, sizeof(v));
                return;
            }
            // if hash is same but value is different
            if (curr->next == NULL){
                curr->next = init_bucket_element(hash,key,v);
                return;
            }
            curr = curr->next;

        }while(1);
    }
}

// fetches value with key
element * get_element(hashMapElement *map, char key[]){ // retunerer en pointer til en function
    int hash = generate_hash_string(key);
    struct bucket_element * curr = map->b[hash];

    if (curr == NULL){ // if nothing on index
        return NULL;
    }
    // if something on index
    do{ 
        // if match
        if (strcmp(key, curr->key) == 0){
            return (element *)curr->value;
        }
        curr = curr->next;

    }
    while(curr != NULL);

    // if something on index but no match
    return NULL;
}


// int main(){
//     hashMapElement map = init_hashMap_element();
//     put(&map, "test", "1");
//     put(&map, "temp", "2");
//     put(&map, "telt", "3");
//     put(&map, "test", "3");

//     char c[50];

//     strcpy(c, get(&map, "test"));
//     printf("%s", c);
//     return 0;

// }