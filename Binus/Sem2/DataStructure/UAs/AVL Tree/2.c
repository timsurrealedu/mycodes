#include <corecrt_math.h>
#include <float.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct node{
    int key;
    struct node* left;
    struct node* right;
    int height;
}node;

node* createNode(int key){
    node* newNode = (node*)malloc(sizeof(node));
    newNode->key=key;
    newNode->right=NULL;
    newNode->left=NULL;
    newNode->height=1;
    return newNode;
}

int maxValue(int a, int b){
    return (a>b)?a:b;
}

int getHeight(node* n){
    if(n==NULL) return 0;
    return n->height;
}

int getBalance(node* n){
    if(n==NULL)return 0;
    return getHeight(n->left) - getHeight(n->right);
}

node* minValueNode(node* n){
    if(n==NULL) return NULL;
    node* curr = n;
    while(curr->left!=NULL){
        curr = curr->left;
    }
    return curr;
}

node* rightRotate(node* a){
    node* b = a->left;
    node* e = b->right;

    b->right=a;
    a->left=e;

    a->height=1+maxValue(getHeight(a->left),getHeight(a->right));
    b->height=1+maxValue(getHeight(b->left),getHeight(b->right));
    return b;
}

node* leftRotate(node* a){
    node* c = a->right;
    node* d = c->left;
    c->left=a;
    a->right=d;

    a->height=1+maxValue(getHeight(a->left),getHeight(a->right));
    c->height=1+maxValue(getHeight(c->left),getHeight(c->right));

    return c;
}

node* insert(node* n, int key){
    if(n==NULL) return createNode(key);

}
