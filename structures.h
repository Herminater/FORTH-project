#include <stdbool.h>

typedef struct{
    int data;
} elm;

typedef struct{
    elm content;
    struct node * next;
    bool ok;
} node;

typedef struct{
    node *last;
    int num;    
} stack;
