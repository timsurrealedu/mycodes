#include <stdio.h>
#include <stdlib.h>

typedef struct node{
    int key;
    struct node* left;
    struct node* right;
    int height;
}node;

int getMax(int a, int b){
    return (a>b)?a:b;
}

int getHeight(node* n){
    if(n==NULL){
        return NULL;
    }
    return n->height;
}

int getBalance(node* n){
    if(n==NULL){
        return 0;
    }
    return getHeight(n->left)-getHeight(n->right);
}

node* rightRotate(node* a){
    node* b = a->left;
    node* e = b->right;

    b->right=a;
    a->left=e;

    a->height=1+getMax(getHeight(a->left),getHeight(a->right));
    b->height=1+getMax(getHeight(b->left),getHeight(b->right));
    return b;
}

