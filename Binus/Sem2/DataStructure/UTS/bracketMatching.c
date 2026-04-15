#include <stdio.h>
#include <stdlib.h>

typedef struct node{
    char brack;
    struct node* next;
    struct node* prev;
}node;

node* head = NULL, *tail = NULL;

node* createNode(char brack){
    node* newNode = (node*)malloc(sizeof(node));
    newNode->brack=brack;
    newNode->next=NULL;
    newNode->prev=NULL;
    return newNode;
}

void push(char brack){
    node* newNode = createNode(brack);
    if(head==NULL){
        head = tail = newNode;
        return;
    }
    newNode->next=head;
    head->prev=newNode;
    head=newNode;
}

void pop(){
    if(head==NULL){
        return;
    }
    node* temp = head;
    head = head->next;
    if(head!=NULL){
        head->prev=NULL;       
    }

    free(temp);
}

int checkBrack(char brack1, char brack2){
    if(brack1=='('&&brack2==')'||brack1=='{'&&brack2=='}'||brack1=='['&&brack2==']'){
        return 1;
        
    }
    return 0;
}

int main(){
    int x;
    scanf("%d",&x);getchar();
    for(int i = 0; i<x;i++){
        char brack;
        scanf("%c",&brack);
        if(brack=='('||brack=='{'||brack=='['){
            push(brack);
        }
        else if(checkBrack(head->brack,brack)==1) {
            pop();
            
        }
    }
    if(head==NULL){
        printf("balanced\n");
    }
    else{
        printf("not balanced\n");
    }
}