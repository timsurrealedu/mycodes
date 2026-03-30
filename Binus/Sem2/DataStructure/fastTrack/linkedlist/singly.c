#include <stdio.h>
#include <stdlib.h>

typedef struct{
    int value;
    struct node* next;
}node;

node* head = NULL, *tail = NULL;

node* createNode(int value){
    node* newNode = (node*)malloc(sizeof(node));
    newNode->value=value;
    newNode->next=NULL;
    return newNode;
}

node* pushHead(int value){
    node* newNode = createNode(value);
    if(head==NULL){
        head = tail = newNode;        
    }
    else{
        newNode->next=head;
        head=newNode;
    }
}

node* pushTail(int value){
    node* newNode = createNode(value);
    if(tail==NULL){
        head=tail=newNode;
    }else{
        tail->next=newNode;
        tail=newNode;
    }
}

node* pushSort(int value){
    
}