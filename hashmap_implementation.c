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

typedef struct bucket{
    int hash;
    char key[KEY_MAX_LENGTH];
    int value;
    struct bucket * next;
} bucket;

typedef struct hashMap{
    bucket * b[HASH_LENGTH];
} hashMap;

// generates hashvalue and assigns index within max_length of the hash map
int generate_hash(char key[]){
    int first = (int)key[0]*100;
    int second = (int)key[1]*1000;
    int hash = (first+second)%(HASH_LENGTH-1);
    return hash;
}

// creates a new bucket for the hashmap
bucket * init_bucket(int hsh, char k[], int value){ 
    bucket *bu = (bucket *) malloc(sizeof(bucket));
    bu->hash = hsh;
    strcpy(bu->key, k); // dette kan blive et problem med allokering af plads og overflow
    bu->value = value;
    bu->next = NULL;
    return bu;
}

// initializes an empty hashmap with size hash_length
hashMap init_hashMap(){
    struct hashMap map;
    for (int i=0; i<HASH_LENGTH; i++){
        map.b[i] = NULL;
    }
    return map;

}

// inserts key,value pair into hashmap
void put(hashMap *map, char key[], int val){
    int hash = generate_hash(key);

    // check for colisions
    // if no collisions:
    if (map->b[hash] == NULL){
        map->b[hash] = init_bucket(hash, key, val);
        
    }
    // if colission
    else{
        struct bucket * curr = map->b[hash];
        do{ 
            // if value allready present:
            if (strcmp(key, curr->key) == 0){ 
                curr->value = val;
                return;
            }
            // if hash is same but value is different
            if (curr->next == NULL){
                curr->next = init_bucket(hash,key,val);
                return;
            }
            curr = curr->next;

        }while(1);
    }
}

// fetches value with key
int get(hashMap *map, char key[]){
    int hash = generate_hash(key);
    struct bucket * curr = map->b[hash];

    if (curr == NULL){ // if nothing on index
        return -11111;
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
    return -11111;   
}

int main(){
    hashMap map = init_hashMap();
    int hash = generate_hash("test");
    bucket new_b = *init_bucket(hash, "test", 1);

    put(&map, "test", 1);
    put(&map, "temp", 2);
    put(&map, "telt", 3);
    put(&map, "test", 3);


    int val = get(&map, "test");
    int val2 = get(&map, "temp");
    int val3 = get(&map, "telt");

    printf("test er %d\n", val);
    printf("temp er %d\n", val2);
    printf("telt er %d\n", val3);

}