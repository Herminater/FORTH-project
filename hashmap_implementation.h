#include <string.h>
#include <stdlib.h>

#define HASH_LENGTH 100 
#define KEY_MAX_LENGTH 50

typedef struct bucket{
    int hash;
    char key[KEY_MAX_LENGTH];
    int value;
    struct bucket * next;
};

typedef struct hashMap{
    struct bucket * b[HASH_LENGTH];
};

int generate_hash(char key[KEY_MAX_LENGTH]){
    int first = (int)key[0]*100;
    int second = (int)key[1]*1000;
    int hash = (first+second)%HASH_LENGTH;
    return hash;
}

bucket init_bucket(int hsh, char key[KEY_MAX_LENGTH], int value){
    bucket b;
    b.hash = hsh;
    b.value = value;
    b.next = (struct bucket *)malloc(sizeof(struct bucket));
    return b;
}

hashMap init_hashMap(){
    struct hashMap map;
    for (int i=0; i<HASH_LENGTH; i++){
        map.b[i] = NULL;
    }
    return map;

}

void put(hashMap *map, char key[KEY_MAX_LENGTH], int val){
    int hash = generate_hash(key);
    struct bucket * new_b = &init_bucket(hash, key, val);

    bucket * curr = map->b[hash];

    // check for colisions
    if (curr == NULL){
        curr = new_b;
    }
    else{
        
    }


    bucket 
}

int main(){

}