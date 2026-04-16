#include <stdio.h>
#include <stdlib.h>

typedef struct node{
    int value;
    struct node* next;
    struct node* prev;
}node;

node* head = NULL, *tail=NULL;

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
    if(head==NULL){
        head=tail=newNode;
        return;
    }
    tail->next=newNode;
    newNode->prev=tail;
    tail=newNode;
}

void pushSort(int value){
    node* newNode=createNode(value);
    if(head==NULL){
        head=tail=newNode;
        return;
    }
    if(value<=head->value){
        pushHead(value);
        free(newNode);
        return;
    }
    if(value>=tail->value){
        pushTail(value);
        free(newNode);
        return;
    }
    node* curr = head;
    while(curr->next!=NULL&&curr->next->value<value){
        curr=curr->next;
    }
    node* temp = curr->next;
    curr->next=newNode;
    newNode->prev=curr;
    newNode->next=temp;
    temp->prev=newNode;
}

void popHead(){
    if(head==NULL){
        printf("head is empty\n");
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
        printf("tail is empty\n");
        return;
    }
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

void popSearch(int value){
    if(head==NULL){
        printf("list is empty\n");
        return;
    }
    if(value==head->value){
        popHead();
        return;
    }
    if(value==tail->value){
        popTail();
        return;
    }
    node* curr=head;
    while(curr->next!=NULL && curr->next->value!=value){
        curr = curr->next;
    }
    if(curr->next==NULL){
        printf("value not found\n");
        return;
    }
    node* temp = curr->next;
    curr->next=curr->next->next;
    temp->next->prev=curr;
    free(temp);
}

void viewNode(){
    if(head==NULL){
        printf("list is empty\n");
        return;
    }
    node* curr = head;
    while(curr){
        printf("%d", curr->value);
        if(curr->next!=NULL){
            printf(" ");
        }else{
            printf("\n");
        }
        curr = curr->next;
    }
}

int main(){
    pushTail(10);
    pushHead(1);
    pushHead(4);
    viewNode();
    pushTail(6);
    popSearch(4);
    viewNode();
    popSearch(6);
    popTail();
    viewNode();
}