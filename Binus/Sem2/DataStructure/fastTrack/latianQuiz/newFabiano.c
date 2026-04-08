#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node{
    char name[100];
    int value;
    struct node* next;
    struct node* prev;
}node;

node* head = NULL, *tail=NULL;

node* createNode(int value, char* name){
    node* newNode = (node*)malloc(sizeof(node));
    newNode->value=value;
    strcpy(newNode->name,name);
    newNode->next=NULL;
    newNode->prev=NULL;
    return newNode;
}

void pushHead(int value, char* name){
    node* newNode = createNode(value,name);
    if(head==NULL){
        head=tail=newNode;
        return;
    }
    newNode->next=head;
    head->prev=newNode;
    head=newNode;
}

void pushTail(int value, char* name){
    node* newNode=createNode(value,name);
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
        printf("list is empty\n");
        return;
    }
    if(head==tail){
        free(head);
        head=tail=NULL;
        return;
    }
    node* temp = head;
    head=head->next;
    free(temp);
    head->prev=NULL;
}

void popTail(){
    if(head==NULL){
        printf("list is empty\n");
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

int main(){
    int a;
    scanf("%d",&a);
    for(int i = 0 ; i < a ; i++){
        int num;
        scanf("%d",&num);
        if(num==1){
            int val;
            char name[100];
            scanf("%d %s",&val,name);getchar();
            pushTail(val,name);
        }else if(num==2){
            if(head==NULL){
                printf("no data\n");
                continue;
            }
            printf("%d %s\n",head->value,head->name);
            popHead();
        }else if(num==3){
            if(head==NULL){
                printf("no data\n");
                continue;
            }
            printf("%d %s\n",head->value,head->name);
        }
    }
}