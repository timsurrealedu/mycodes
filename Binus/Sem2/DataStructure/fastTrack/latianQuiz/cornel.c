#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node{
    int value;
    struct node* next;
    struct node* prev;
}node;

node* head = NULL, *tail =NULL;

node* createNode(int value){
    node* newNode = (node*)malloc(sizeof(node));
    newNode->next=NULL;
    newNode->prev=NULL;
    newNode->value=value;
    return newNode;
}

void pushHead(int value){
    node* newNode=createNode(value);
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
    newNode->prev=tail;
    tail->next=newNode;
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
    node* temp = tail;
    tail = tail->prev;
    tail->next=NULL;
    free(temp);
}
int anything=2;
void popSearch(int value){
    if(head==NULL){
        printf("nothing to pop\n");
        anything=0;
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
        curr=curr->next;
    }
    if(curr->next==NULL){
        printf("value not found\n");
        anything = 0;
        return;
    }
    node* temp = curr->next;
    
    curr->next->next->prev=curr;
    curr->next=curr->next->next;
    free(temp);
}

void viewNode(){
    if(head==NULL){
        printf("its empty\n");
        return;
    }
    node* curr = head;
    while(curr){
        printf("%d", curr->value);
        if(curr->next){
            printf(" ");
        }
        curr=curr->next;
    }
    printf("\n");
}

int main(){
    int N, Q;
    scanf("%d %d",&N,&Q);getchar();
    for(int i=0;i<N;i++){
        pushTail(i+1);
    }
    
    for(int i=0;i<Q;i++){
        int num;
        scanf("%d",&num);getchar();
        popSearch(num);
        if(anything==0){
            anything=2;
            continue;
        }else{
            pushTail(num);
        }
        viewNode();

    }
}