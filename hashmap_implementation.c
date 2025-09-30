#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#define HASH_LENGTH 10
#define KEY_MAX_LENGTH 5

typedef struct bucket{
    int hash;
    char key[KEY_MAX_LENGTH];
    int value;
    struct bucket * next;
} bucket;

typedef struct hashMap{
    struct bucket * b[HASH_LENGTH];
} hashMap;

int generate_hash(char key[]){
    int first = (int)key[0]*100;
    int second = (int)key[1]*1000;
    int hash = (first+second)%(HASH_LENGTH-1);
    return hash;
}

bucket * init_bucket(int hsh, char k[], int value){ 
    bucket *bu = (bucket *) malloc(sizeof(bucket));
    bu->hash = hsh;
    strcpy(bu->key, k); // dette kan blive et problem med allokering af plads og overflow
    bu->value = value;
    bu->next = NULL;
    return bu;
}

hashMap init_hashMap(){
    struct hashMap map;
    for (int i=0; i<HASH_LENGTH; i++){
        map.b[i] = NULL;
    }
    return map;

}

void put(hashMap *map, char key[], int val){
    int hash = generate_hash(key);
    bucket new_b = *init_bucket(hash, key, val);

    // check for colisions
    if (map->b[hash] == NULL){
        printf("H");
        map->b[hash] = &new_b;
    }
    else{
        struct bucket * curr = map->b[hash];

        do{
            if (strcmp(key, curr->key) == 0){
                map->b[hash] = &new_b;
                return;
            }
            curr = curr->next;

        }while(curr->next != NULL);

        curr->next = &new_b;
    }
}

int get(hashMap *map, char key[]){
    int hash = generate_hash(key);

    struct bucket * curr = map->b[hash];

    if (curr == NULL){
        return -11111;
    }

    do{
            if (strcmp(key, curr->key) == 0){
                return curr->value;
            }
            curr = curr->next;

        }while(curr != NULL);

    return -11111;   
}


int main(){
    hashMap map = init_hashMap();
    int hash = generate_hash("test");
    bucket new_b = *init_bucket(hash, "test", 1);

    put(&map, "test", 1);
    put(&map, "temp", 2);
    put(&map, "telt", 3);

    int val = get(&map, "test");
    int val2 = get(&map, "temp");
    int val3 = get(&map, "telt");

    printf("test er %d", val);
    printf("temp er %d", val2);
    printf("telt er %d", val3);

    

}