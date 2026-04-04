#include <stdio.h>
#include <stdlib.h>

typedef struct node{
    char c;
    struct node* next;
}node;

node* head = NULL, *tail = NULL;

node* createNode(char c){
    node* newNode=(node*)malloc(sizeof(node));
    newNode->c=c;
    newNode->next=NULL;
    return newNode;
}

void push(char c){
    node* newNode = createNode(c);
    if(head==NULL){
        head=tail=newNode;
        return;
    }
    newNode->next=head;
    head=newNode;
}

void pop(char c){
    
}