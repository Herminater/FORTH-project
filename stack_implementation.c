#include <stdio.h>
#include "structures.h"
#include <stdlib.h>
#include <stdbool.h>
// source for node
// https://www.geeksforgeeks.org/c/c-program-for-inserting-a-node-in-a-linked-list/

/*
Functions: 
    init_stack() -> stack
    init_elm(int k) -> elm
    init_node(elm e) -> node *
    make_test_node(int k) -> node * 
    append_stack(stack *s, node * n) -> void
    print_stack(stack *s) -> void

Structs from structures.h
    elm(int)
    node(elm)
    stack()
*/

// makes empty stack
stack init_stack(){
    stack s;
    s.num = 0;
    return s;
}

// makes empty elm (type comming soon)
elm init_elm(int k){
    elm e;
    e.data = k;
    return e;
}

// makes a node 
node * init_node(elm e){
    node *n = (node *) malloc(sizeof(node)); // se source i toppen for dokumentation of forklaring
    n->content = e;
    n->ok = true;
    return n;
}

// makes a node with content e
node * make_test_node(int k){
    elm e = init_elm(k);
    node * n = init_node(e);
    return n;
}

// takes pointer to stack and node and appends node to stack
void append_stack(stack *s, node * n){
    //empty stack
    if (s->num == 0){
        s->last = n;
        s->num += 1;
        return;
    }
    //not empty stack
    n->next = (struct node *) s->last;
    s->last = n;
    s->num += 1;  
} 

node * pop_stack(stack *s){
    node * temp;
    // if empty set ok to false indicating false
    if (s->num == 0){ 
        temp = (node *) malloc(sizeof(node));
        temp->ok = false;
        return temp;
    } 

    temp = s->last;

    s->last = (node *)temp->next;
    s->num -= 1;

    return temp;
}


// prints stack going from last to first
void print_stack(stack *s){
    node * n = s->last;
    for (int i=0; i<s->num;i++){
        printf("%d", n->content.data);
        n = (node *)n->next;
    }
}

int main(){
    node* l[5];
    stack s = init_stack();
    for (int i=0;i<5;i++){
        node * n = make_test_node(i);
        l[i] = n;
        append_stack(&s, n);
    }
    pop_stack(&s);

    print_stack(&s);
    
}