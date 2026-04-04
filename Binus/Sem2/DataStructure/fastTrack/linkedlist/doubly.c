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
    node* newNode = createNode(value);
    if(head==NULL){
        head=tail=newNode;
        return;
    }
    if(head->value>=value){
        newNode->next=head;
        head->prev=newNode;
        head=newNode;
        return;
    }
    if(tail->value<=value){
        tail->next=newNode;
        newNode->prev=tail;
        tail=newNode;
        return;
    }
    node* curr=head;
    while(curr->value<=value&&curr->next!=NULL){
        curr=curr->next;
    }
    curr->prev->next=newNode;
    newNode->prev=curr->prev;
    curr->prev=newNode;
    newNode->next=curr; 
}

void popHead(){
    if(head==NULL){
        printf("list is empty\n");
        return;
    }if(head==tail){
        free(head);
        head=tail=NULL;
        return;
    }node* temp = head;
    head=head->next;
    head->prev=NULL;
    free(temp);
}

void popTail(){
    if(head==NULL){
        printf("list is empty\n");
        return;
    }if(head==tail){
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
    if(head->value==value){
        popHead();
        return;
    }if(tail->value==value){
        popTail();
        return;
    }
    node* curr = head;
    while(curr->value!=value&&curr->next!=NULL){
        curr=curr->next;
    }
    if(curr->value!=value){
        printf("value not found\n");
        return;
    }
    node* temp = curr;
    curr->prev->next=curr->next;
    curr->next->prev=curr->prev;
    free(temp);
    

}

void viewNode(){
    if(head==NULL){
        printf("list is empty\n");
        return;
    }
    node* curr = head;
    while(curr){
        printf("%d ", curr->value);
        curr=curr->next;
    }

    printf("\n");
}

void clearNode(){
    while(head){
        node* temp=head;
        head=head->next;
        free(temp);
        temp=NULL;
    }
    tail=NULL;
}

int main(){
    pushHead(1);
    pushTail(2);
    pushTail(3);
    pushTail(8);
    pushSort(4);
    viewNode();
    popHead();
    popTail();
    popSearch(3);
    viewNode();
    clearNode();
    viewNode();
}