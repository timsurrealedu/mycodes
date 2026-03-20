#include <stdio.h>
#include <stdlib.h>

struct node {
    int val;
    struct node *next;
};

void initnode(struct node *node, int val){
    node->val = val;
    node->next = null;
}

struct stack {
    struct node *head;
};

int isempty(struct stack *st){
    return st->head == null;
}

void initstack(struct stack *st){
    st->head = null;
}

void push(struct stack *st,int val){

}

void pop(struct stack *st){

}

int top(struct stack *st){
    assert(st->head != null);
    return st->head->val;

}

int main(){
    struct 
}