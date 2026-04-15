#include <stdio.h>
#include <stdlib.h>

typedef struct node{
    int value;
    struct node* next;
    struct node* prev;
}node;

node* head = NULL;
node* tail = NULL;

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

void popHead(){
    if(head==NULL){
        printf("already empty\n");
        return;
    }
    node* temp = head;
    head = head->next;
    head->prev=NULL;
    free(temp);
}

void popTail(){
    if(head==NULL){
        printf("already empty\n");
        return;
    }
    node* temp = tail;
    tail = tail->prev;
    tail->next=NULL;
    free(temp);
}

void pushSort(int value){
    if(head==NULL){
        pushHead(value);
        return;
    }
    if(value<=head->value){
        pushHead(value);
        return;
    }
    if(value>=tail->value){
        pushTail(value);
        return;
    }
    node* curr = head;
    while(curr->next!=NULL&&curr->next->value<value){
        curr=curr->next;
    }
    node* newNode=createNode(value);
    node* temp = curr->next;
    curr->next=newNode;
    newNode->prev=curr;
    temp->prev=newNode;
    newNode->next=temp;
}

void printNode(){
    if(head==NULL){
        printf("empty list\n");
        return;
    }
    node* curr = head;
    while(curr){
        printf("%d ", curr->value);
        curr = curr->next;

    }
    printf("\n");
}

void popSearch(int value){
    if(head==NULL){
        printf("empty list\n");
        return;
    }
    if(head->value==value){
        popHead();
        return;
    }
    if(tail->value==value){
        popTail();
        return;
    }

    node* curr = head;
    while(curr->next!=NULL&&curr->next->value!=value){
        curr = curr->next;
    }
    if(curr->next==NULL){
        printf("not found\n");
        return;
    }
    node* temp = curr->next;
    curr->next->next->prev=curr;
    curr->next=temp->next;
    free(temp);

}

int main(){
    pushHead(1);
    pushHead(0);
    pushTail(5);
    pushSort(3);
    popSearch(3);
    printNode();

}