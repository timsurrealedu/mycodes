#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
    if(head->value>=value){
        pushHead(value);
        return;
    }
    if(tail->value<=value){
        pushTail(value);
        return;
    }
    node* newNode = createNode(value);
    node* curr = head;
    while(curr->next!=NULL&&curr->next->value<value){
        curr=curr->next;
    }
    node* temp = curr->next;
    newNode->prev=curr;
    newNode->next=curr->next;
    curr->next=newNode;
    temp->prev=newNode;
}

void popHead(){
    if(head==NULL){
        printf("nothing to pop\n");
        return;
    }
    if(head==tail){
        free(head);
        head=tail=NULL;
        return;
    }
    node* temp = head;
    head=head->next;
    head->prev=NULL;
    free(temp);
}

void popTail(){
    if(head==NULL){
        printf("nothing to pop\n");
        return;
    }
    if(head==tail){
        free(head);
        head=tail=NULL;
        return;
    }
    node* temp = tail;
    tail = tail->prev;
    tail->next=NULL;
    free(temp);
}

void popSearch(int value){
    if(head==NULL){
        printf("nothing to pop\n");
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
    node* curr=head;
    while(curr->next!=NULL&&curr->next->value!=value){
        curr = curr->next;
    }
    if(curr->next==NULL){
        printf("value not found\n");
        return;
    }
    node* temp = curr->next->next;
    node* temp2 = curr->next;
    curr->next=curr->next->next;
    temp->prev=curr;
    free(temp2);
}
void viewNode(){
    node* curr = head;
    while(curr){
        printf("%d ", curr->value);
        curr= curr->next;
    }
    printf("\n");
    return;
}

int main(){
    pushHead(3);
    pushHead(1);
    pushSort(2);
    viewNode();
    pushSort(4);
    pushTail(8);
    pushSort(0);
    pushSort(10);
    viewNode();
    popHead();
    viewNode();
    popTail();
    viewNode();
    popSearch(13);
    viewNode();

}