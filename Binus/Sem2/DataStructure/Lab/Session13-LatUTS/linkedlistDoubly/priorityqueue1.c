#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

struct Node {
    int p;
    struct Node* next;
    struct Node* prev;
};

void initNode(struct Node* node, int p){
    node->p = p;
    node->next = node->prev = NULL;
}

struct PQ{
    struct Node* head;
    struct Node* tail;
};

void initPQ(struct PQ *pq){
    pq->head = pq->tail = NULL;
}

void push(int p){   

}

void pop(struct PQ){}

void top(struct PQ*)