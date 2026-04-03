#include <stdio.h>
#include <stdlib.h>

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

void push(int value){
    node* newNode = createNode(value);
    if(head==NULL){
        head=tail=newNode;
        return;
    }
    newNode->next=head;
    head->prev=newNode;
    head=newNode;
}

void pop(){
    if(head==NULL){
        printf("list is empty\n");
        return;
    } 
    if(head==tail){
        free(head);
        head=tail=NULL;
        return;
    }
    node* temp = head;
    head = head->next;
    head->prev=NULL;
    temp->next=NULL;
    free(temp);
}

void viewStack(){
    
}