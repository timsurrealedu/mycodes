#include <stdio.h>
#include <stdlib.h>

struct Node {
    int val;
    struct Node *next;
};

void initNode(struct Node *node, int val){
    node->val = val;
    node->next = NULL;
}

struct LinkedList{
    struct Node *head;
};

void pushHead(struct LinkedList *list, int val){
    struct Node *newNode = (struct Node*)malloc(sizeof(struct Node));
    initNode(newNode, val);
    newNode->next=list->head;
    list->head=newNode;
}

void pushTail(struct LinkedList *list, int val){
    struct Node *newNode = (struct Node*)malloc(sizeof(struct Node));
    initNode(newNode, val);
    if(list->head == NULL){
        list->head=newNode;
        return;
    }
    struct Node *cur = list->head;
    while(cur->nexrt != NULL){
        cur = cur->next;
    }
    struct Node *cur = list->head;
    while
}