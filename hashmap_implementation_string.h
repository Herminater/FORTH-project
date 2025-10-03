#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#define HASH_LENGTH 100
#define KEY_MAX_LENGTH 50

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

typedef struct bucket_string{
    int hash;
    char key[KEY_MAX_LENGTH];
    char value[50];
    struct bucket_string * next;
} bucket_string;

typedef struct hashMapString{
    bucket_string * b[HASH_LENGTH];
} hashMapString;

// generates hashvalue and assigns index within max_length of the hash map
int generate_hash_string(char key[]){
    int first = (int)key[0]*100;
    int second = (int)key[1]*1000;
    int hash = (first+second)%(HASH_LENGTH-1);
    return hash;
}

// creates a new bucket for the hashmap
bucket_string * init_bucket_string(int hsh, char k[], char value[]){ 
    bucket_string *bu = (bucket_string *) malloc(sizeof(bucket_string));
    bu->hash = hsh;
    strcpy(bu->key, k); // dette kan blive et problem med allokering af plads og overflow
    strcpy(bu->value, value); // dette kan blive et problem med allokering af plads og overflow
    bu->next = NULL;
    return bu;
}

// initializes an empty hashmap with size hash_length
hashMapString init_hashMap_string(){
    struct hashMapString map;
    for (int i=0; i<HASH_LENGTH; i++){
        map.b[i] = NULL;
    }
    return map;

}

// inserts key,value pair into hashmap
void put_string(hashMapString *map, char key[], char val[]){
    int hash = generate_hash_string(key);

    // check for colisions
    // if no collisions:
    if (map->b[hash] == NULL){
        map->b[hash] = init_bucket_string(hash, key, val);
        
    }
    // if colission
    else{
        struct bucket_string * curr = map->b[hash];
        do{ 
            // if value allready present:
            if (strcmp(key, curr->key) == 0){ 
                strcpy(curr->value, val); // dette kan blive et problem med allokering af plads og overflow
                return;
            }
            // if hash is same but value is different
            if (curr->next == NULL){
                curr->next = init_bucket_string(hash,key,val);
                return;
            }
            curr = curr->next;

        }while(1);
    }
}

// fetches value with key
char * get_string(hashMapString *map, char key[]){ // retunerer en pointer til en function
    int hash = generate_hash_string(key);
    struct bucket_string * curr = map->b[hash];

    if (curr == NULL){ // if nothing on index
        return NULL;
    }
    // if something on index
    do{ 
        // if match
        if (strcmp(key, curr->key) == 0){
            return curr->value;
        }
        curr = curr->next;

    }
    while(curr != NULL);

    // if something on index but no match
    return NULL;
}


// int main(){
//     hashMap map = init_hashMap();
//     put(&map, "test", "1");
//     put(&map, "temp", "2");
//     put(&map, "telt", "3");
//     put(&map, "test", "3");

//     char c[50];

//     strcpy(c, get(&map, "test"));
//     printf("%s", c);
//     return 0;

// }