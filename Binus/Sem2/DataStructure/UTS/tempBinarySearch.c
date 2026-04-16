#include <stdio.h>
#include <stdlib.h>

typedef struct node{
    int value;
    struct node* left;
    struct node* right;
}node;

node* createNode(int value){
    node* newNode = (node*)malloc(sizeof(node));
    
}
