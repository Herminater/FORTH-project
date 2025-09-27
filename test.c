#include <stdio.h>
#include "structures.h"
#include <stdlib.h>
// source for node
// https://www.geeksforgeeks.org/c/c-program-for-inserting-a-node-in-a-linked-list/

stack init_stack(){
    stack s;
    s.num = 0;
    return s;
}
elm init_elm(int k){
    elm e;
    e.data = k;
    return e;
}

node * init_node(elm e){
    node *n = (node *) malloc(sizeof(node));
    n->content = e;
    return n;
}

node * make_test_node(int k){
    elm e = init_elm(k);
    node * n = init_node(e);
    return n;
}

void append_stack(stack *s, node * n){
    if (s->num == 0){
        s->last = n;
        s->num += 1;
        return;
    }
    n->next = (struct node *) s->last;
    s->last = n;
    s->num += 1;
    
} 


int main(){
    node* l[5];
    stack s = init_stack();
    for (int i=0;i<5;i++){
        node * n = make_test_node(i);
        l[i] = n;
        append_stack(&s, n);
    }



    // for (int i=0; i<5; i++){
    //     printf("%d, next = %d ", l[i]->content.data, 1);
    // }
    node * n = s.last;
    for (int i=0; i<5;i++){
        printf("%d", n->content.data);
        n = (node *)n->next;
    }
}