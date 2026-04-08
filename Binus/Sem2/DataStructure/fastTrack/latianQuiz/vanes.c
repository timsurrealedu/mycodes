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
    node* newNode=(node*)malloc(sizeof(node));
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
    node* temp=tail;
    tail=tail->prev;
    tail->next=NULL;
    free(temp);
}

int main(){
    int N, Q;
    scanf("%d %d",&N,&N);
    for(int i = 0 ; i < N ; i++){
        
    }
}