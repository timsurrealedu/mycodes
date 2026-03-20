#include <stdio.h>
#include <stdlib.h>

typedef struct Node{
    int data;
    struct Node* next;
}Node;

Node* createNode(int value){
    Node* n = malloc(sizeof(Node));
    n->data=value;
    n->next=NULL;
    return n;
}

Node* pushHead(Node* head, int value){
    Node* n = createNode(value);
    n->next = head;
    return n;
}

Node* pushTail(Node* head, int value){
    Node* n = createNode(value);
    Node* current = head;
    while(current->next!=NULL){
        current = current->next;
    }current->next = n;
}

Node* pushMid(Node* head, int value, int position){
    if(position==0){
        return pushHead(head, value);
    }
    Node* n = createNode(value);
    Node* current = head;

    for(int i = 0 ; i < position - 1 ; i++){
        if(current->next == NULL){
            printf("position out of range\n");
            return head;
        }
    }
}
