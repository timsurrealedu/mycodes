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

void pushTail(int value){
    node* newNode=createNode(value);
    if(head==NULL){
        head=tail=newNode;
        return;
    }
    tail->next=newNode;
    newNode->prev=tail;
    tail=newNode;
}

void popHead(){
    if(head==NULL){
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
    free(temp);
}

void popTail(){
    if(head==NULL){
        return;
    }
    if(head==tail){
        free(head);
        head=tail=NULL;
    }
    node* temp = tail;
    tail = tail->prev;
    tail->next=NULL;
    free(temp);
}

void popSearch(int value){
    if(head==NULL){
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
    node* curr = head;
    while(curr->next!=NULL&&curr->next->value!=value){
        curr=curr->next;
    }
    if(curr->next==NULL){
        return;
    }
    node* temp = curr->next;
    curr->next=curr->next->next;
    temp->next->prev=curr;
    free(temp);
}

void viewNode(){
    if(head==NULL){
        printf("-1\n");
        return;
    }
    node* curr=head;
    while(curr){
        printf("%d", curr->value);
        if(curr->next!=NULL){
            printf(" ");
        }else{
            printf("\n");
        }
        curr=curr->next;
    }
}

int main(){
    int N;
    scanf("%d", &N);
    for(int i = 0 ; i < N; i++){
        int temp;
        scanf("%d", &temp);
        pushTail(temp);
    }
    node* curr = head;
    int count = 0;
    int toBeDel[N+2];
    while(curr){
        if(curr->value%2!=0){
            toBeDel[count]=curr->value;
            count++;
            curr = curr->next;
        }else{
            curr = curr->next;
        }
        
    }
    for(int i = 0 ; i<count;i++){
        popSearch(toBeDel[i]);
    }
    viewNode();
    
}