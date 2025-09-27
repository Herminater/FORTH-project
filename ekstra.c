




struct node* pop_stack(stack *s){
    node * temp;
    if (s->num == 0) return temp;

    temp = s->last;
    s->last = temp->next;
    s->num -= 1;
}


void print_stack(stack *s){
    struct node * curr = s->last;
    for (int i=1; i<s->num; i++){
        printf("%d", curr->content.data);
        curr = curr->next;
    }
}


int main(){
    struct stack s = init_stack();

    for (int i = 0; i<5; i++){
        struct node one = make_test_node(1);
        append_stack(&s, &one);
    }

    print_stack(&s);

    
}