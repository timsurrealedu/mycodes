#include <stdio.h>
#include <stdlib.h>

typedef struct node{
    int value;
    struct node* next;
    struct node* prev;
}node;

node* head= NULL, *tail=NULL;

node* createNode(int value){
    node* newNode = (node*)malloc(sizeof(node));
    newNode->value=value;
    newNode->next=NULL;
    newNode->prev=NULL;
    return newNode;
}

void pushHead(int value){
    node* newNode = createNode(value);
    if(head == NULL){
        head = tail = newNode;
        return;
    }
    newNode->next=head;
    head->prev=newNode;
    head = newNode;
    return;
}

void pushTail(int value){
    node* newNode = createNode(value);
    if(tail == NULL){
        head = tail = newNode;
        return;
    }
    tail->next=newNode;
    newNode->prev=tail;
    tail=newNode;
}

void pushSearch(int value, int order, int length){
    node* newNode = createNode(value);
    if(head==NULL){
        pushHead(newNode);
        return;
    }
    if(order == 1){
        pushHead(newNode);
        return;
    }
    if(order >= length){
        pushTail(newNode);
        return;
    }
    order -=1;
    node* curr = head;
    int tempOrder = 0;
    while(tempOrder<order){
        curr = curr->next;
        tempOrder++;
    }
    node* temp = curr->prev;
    temp->next=newNode;
    newNode->prev=temp;
    curr->next->prev=newNode;
    newNode->next=curr->next;
}

void popHead(){
    if(head==NULL){
        printf("already empty\n");
        return;
    }
}

int main(){
    return 0;
}