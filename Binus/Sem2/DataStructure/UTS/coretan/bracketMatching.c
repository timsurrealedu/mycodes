#include <stdio.h>
#include <stdlib.h>

typedef struct node{
    char brack;
    struct node* next;
}node;

node* head = NULL, *tail = NULL;

node* createNode(char brack){
    node* newNode = (node*)malloc(sizeof(node));
    newNode->brack=brack;
    newNode->next=NULL;
    return newNode;
}

void push(char brack){
    node* newNode=createNode(brack);
    if(head==NULL){
        head=tail=newNode;
        return;
    }
    newNode->next=head;
    head=newNode;
}

void pop(){
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
    free(temp);
}

int compare(char brack1, char brack2){
    if(brack1=='('&&brack2==')'||brack1=='{'&&brack2=='}'||brack1=='['&&brack2==']'){
        return 1;
    }
    else{
        return 0;
    }
}

int main(){
    int L;
    int possible = 1;
    scanf("%d",&L);
    for(int i = 0 ; i < L ; i++){
        char temp;
        scanf(" %c",&temp);
        if(temp=='('||temp=='{'||temp=='['){
            push(temp);
        }else{
            if(head!=NULL&&compare(head->brack,temp)==1){
                pop();
            }else{
                possible = 0;
                break;
            }
        }
    }
    if(possible==1&&head==NULL){
        printf("balanced\n");
    }else{
        printf("unbalanced\n");
    }
}