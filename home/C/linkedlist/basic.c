#include <stdio.h>
#include <stdlib.h>

typedef struct Node{
    int data;
    struct Node* next;
}Node;

Node* createNode(int value){
    Node* n = malloc(sizeof(Node));
    n->data = value;
    n->next = NULL;
    return n;
}

void printList(Node* head){
    Node* current = head;
    while (current!=NULL){
        printf("%d -> ", current->data);
        current = current->next;
    }
    printf("NULL\n");
}

int main(){
    Node* head = createNode(10);
    Node* second = createNode(20);
    Node* third = createNode(30);

    head->next = second;
    second-> next = third;

    printList(head);

    return 0;
}