typedef struct{
    int data;
} elm;

typedef struct{
    elm content;
    struct node * next;
} node;

typedef struct{
    node *last;
    int num;    
} stack;
