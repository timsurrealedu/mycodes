#include <stdio.h>
#include <stlib.h>

typedef struct node{
    int value;
    struct node* next;
    struct node* prev;
}node;

node* head=NULL, *tail=NULL;

node* createNode(int value){
    node* newNode = (node*)malloc(sizeof(node));
    newNode->value=value;
    newNode->next=NULL;
    newNode->prev=NULL;
    return newNode;
}

void pushHead(int value){
    node* newNode=createNode(value);
    if(head==NULL){
        head=tail=newNode;
        return;
    }head->next=newNode;
    newNode->prev=head;
    head=newNode;
}

void pushTail(int value){
    node* newNode=createNode(value);
    if(tail==NULL){
        head=tail=newNode;
        return;
    }
    newNode->next=tail;
    tail->prev=newNode;
    tail=newNode;
}

void pushSort(int value){
    node* newNode=createNode(value);
    if(head==NULL){
        head=tail=newNode;
        return;
    }
    node* curr=head;
    while(curr->value<=value){
        curr=curr->next;
    }curr->prev=newNode;
    newNode->next=curr;
}

0 1 '2' 3 4 