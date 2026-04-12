#include <stdio.h>
#include <stdlib.h>

typedef struct node{
    int value;
    struct node* next;
    struct node* prev;
}node;

node* head = NULL, *tail = NULL;

node* createNode(int value){
    node* newNode = (node*)malloc(sizeof(node));
    newNode->value=value;
    newNode->next=NULL;
    newNode->prev=NULL;
    return newNode;
}

void pushHead(int value){
    node* newNode = createNode(value);
    if(head==NULL){
        head=tail=newNode;
        return;
    }
    newNode->next=head;
    head->prev=newNode;
    head=newNode;
}

void pushTail(int value){
    node* newNode = createNode(value);
    if(tail==NULL){
        head=tail=newNode;
        return;
    }
    tail->next=newNode;
    newNode->prev=tail;
    tail=newNode;
}

void pushSort(int value){
    if(head==NULL){
        head=tail=createNode(value);
        return;
    }
    if(head->value<=value){
        pushHead(value);
        return;
    }
    if(tail->value>=value){
        pushTail(value);
        return;
    }
    node* curr=head;
    while(curr->next!=NULL&&curr->next->value<value){
        curr = curr->next;
    }
    node* newNode = createNode(value);
    node* temp = curr;
    curr->next=newNode;
    newNode->prev=curr;
    newNode->next = temp->next;
    temp->next->prev=newNode;
}