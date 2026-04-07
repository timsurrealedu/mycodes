#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node{
    char name[100];
    int priority;
    struct node* next;
    struct node* prev;
}node;


node* head = NULL, *tail = NULL;

node* createNode(char* name, int priority){
    node* newNode = (node*)malloc(sizeof(node));
    newNode->next=NULL;
    newNode->prev=NULL;
    newNode->priority=priority;
    strcpy(newNode->name,name);
    return newNode;
}

void pushHead(char* name, int priority){
    node* newNode = createNode(name,priority);
    if(head==NULL){
        head=tail=newNode;
        return;
    }
    newNode->next=head;
    head->prev=newNode;
    head=newNode; 
}

void pushTail(char* name, int priority){
    node* newNode = createNode(name,priority);
    if(tail==NULL){
        head=tail=newNode;
        return;
    }
    tail->next=newNode;
    newNode->prev=tail;
    tail=newNode;
}

void push(char* name, int priority){
    if(head==NULL||head->priority<priority){
        pushHead(name,priority);
        return;
    }
    if(tail->priority>=priority){
        pushTail(name,priority);
        return;
    }
    node* curr = head;
    while(curr->next!=NULL&&curr->next->priority>=priority){
        curr=curr->next;
    }
    node* temp = curr;
    node* newNode = createNode(name,priority);
    newNode->prev=curr;
    newNode->next=curr->next;
    curr->next=newNode;
    if(temp->next!=NULL) temp->next->prev=newNode;
    else{
        tail=newNode;
    }
    // 1 1 1 0
    // 0 0 1
}

void viewNode(){
    if(head==NULL){
        printf("list is empty\n");
        return;
    }
    node* curr = head;
    while(curr){
        printf("%s ",curr->name);
        curr = curr->next;
    }
    printf("\n");
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
    temp->next->prev=head;
    free(temp);
}

void popTail(){
    if(tail==NULL){
        printf("nothing to pop\n");
        return;
    }
    if(head==tail){
        free(head);
        head=tail=NULL;
        return;
    }
    node* temp = tail;
    tail=tail->prev;
    free(temp);
    tail->next=NULL;
}

void cancel(char* name){
    if(head==NULL){
        printf("not found\n");
        return;
    }
    if(strcmp(head->name,name)==0){
        popHead();
        return;
    }
    if(strcmp(tail->name,name)==0){
        popTail();
        return;
    }
    node* curr = head;
    while(curr->next!=NULL&&strcmp(name,curr->next->name)!=0){
        curr = curr->next;
    }
    if(curr->next==NULL){
        printf("not found\n");
        return;
    }
    node* temp = curr->next;
    curr->next=curr->next->next;
    temp->next->prev=curr;
    free(temp);
}

void clearNode(){
    if(head==NULL){
        printf("already empty\n");
        return;
    }
    while(head){
        popHead();
    }

}

void call(){
    if(head==NULL){
        printf("list is empty\n");
        return;
    }
    node* curr = head;
    int num = 1;
    while(curr){
        if(curr->next!=NULL){
            printf("%d %s - %s\n",num, curr->name,curr->next->name);
            num++;
            
        }else{
            printf("%d %s\n",num, curr->name);

        }
        curr = curr->next;
    }
    return;

}

void callC(){
    node *temp = head;
    while(temp != NULL){
        if(temp->next !=NULL){
        printf("%s - %s\n", temp->name, temp->next->name);
        } else {
            printf("%s\n", temp->name);
        }
        temp = temp->next;
    }
}




int main(){
    push("alex",0);
    push("steve",0);
    push("jack",1);
    viewNode();
    call();
    clearNode();
    viewNode();
    push("rexton",0);
    push("ale",1);
    push("cornel",1);
    viewNode();
    //viewNode();
}
