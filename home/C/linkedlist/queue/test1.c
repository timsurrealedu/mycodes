#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

typedef struct node{
    int value;
    struct node* next;
    struct node* prev;
}node;

node* head=NULL, *tail=NULL;

node* createNode(int value){
    node* newNode=(node*)malloc(sizeof(node));
    assert(newNode!=NULL);
    newNode->value=value;
    newNode->next=NULL;
    newNode->prev=NULL;
    return newNode;
}

void push(int value){
    node* newNode=createNode(value);
    if(head==NULL){
        head=tail=newNode;
        return;
    }
    newNode->next=head;
    head->prev=newNode;
    head=newNode;
}

void pop(){
    assert(head!=NULL);
    if(head==tail){
        free(head);
        head=tail=NULL;
        return;
    }
    node* temp = tail;
    tail=tail->prev;
    tail->next=NULL;
    free(temp);
}

void view(){
    assert(head!=NULL);
    node* curr = head;
    while(curr){
        printf("%d ",curr->value);
        curr=curr->next;
    }
    printf("\n");
}

int main(){
    push(4);
    push(3);
    push(2);
    push(1);
    view();
    pop();
    view();
    pop();
    view();
    pop();
    view();
    pop();
    view();
}