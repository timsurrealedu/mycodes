#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

typedef struct node{
    int value;
    struct node* next;
    struct node* prev;
}node;

node* head = NULL, *tail = NULL;

node* createNode(int value){
    node* newNode = (node*)malloc(sizeof(node));
    assert(newNode!=NULL);
    newNode->value=value;
    newNode->next=NULL;
    newNode->prev=NULL;
    return newNode;
}

void push(int value){
    node* newNode = createNode(value);
    assert(newNode!=NULL);
    if(head==NULL){
        head=tail=newNode;
        return;
    }
    
}