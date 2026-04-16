#include <stdio.h>
#include <stdlib.h>

typedef struct node{
    int value;
    struct node* next;
}node;

node* createNode(int value){
    node* newNode = (node*)malloc(sizeof(node));
    newNode->value=value;
    newNode->next=NULL;
    return newNode;
}

void pushTail(node** tail, node** head, int value){
    node* newNode = createNode(value);
    if(*tail==NULL){
        *head =*tail=newNode;
    }
    (*tail)->next=newNode;
    *tail=newNode;
}


int main(){
    node* head1 = NULL, *tail1=NULL;
    node* head2 = NULL, *tail2 = NULL;
    int L;
    scanf("%d", &L);getchar();
    for(int i=0;i<L;i++){
        int temp;
        scanf("%d", &temp);
        pushTail(&tail1, &head1, temp); 
    }
    for(int i=0;i<L;i++){
        int temp;
        scanf("%d", &temp);
        pushTail(&tail2,&head2, temp); 
    }
    int count = 0;
    node* curr1 = head1;
    node* curr2 = head2;
    while(curr1&&curr2){
        if(curr1->value==curr2->value){
            count++;
        } 
        curr1 = curr1->next;
        curr2 = curr2->next;
    }
    printf("%d\n",count);
    
}