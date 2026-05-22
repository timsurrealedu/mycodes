#include <stdio.h>
#include <stdlib.h>

typedef struct node{
    int value;
    struct node* left;
    struct node* right;
    int height;
}node;

node* createNode(int value){
    node* newNode = (node*)malloc(sizeof(node));
    newNode->value=value;
    newNode->height=1;
    newNode->left=NULL;
    newNode->right=NULL;
    return newNode;
}

int maxValue(int a, int b){
    return(a>b)?a:b;
}

int height(node* N){
    if(N==NULL){
        return 0;
    }
    return N->height;
}

node* rightRotate(node* y){
    node* x = y->left;
    node* T2 = x->right;

    x->right=y;
    y->left=T2;

    y->height=maxValue(height(y->left),height(y->right)) + 1;
    x->height=maxValue(height(x->left),height(x->right)) + 1;

    return x;
}

node* leftRotate(node* x){
    node* y = x->right;
    node* T2 = y->left;

    y->left = x;
    x->right = T2;

    x->height=maxValue(height(x->left), height(x->right)) + 1;
    y->height=maxValue(height(y->left), height(y->right)) + 1;
    return y;
}

int getBalance(node* N){
    if(N==NULL) return 0;
    return height(N->left)-height(N->right);
}

node* insert(node* N, int value){
    if(N==NULL) return createNode(value);
    if(value<N->value){
        N->left=insert(N->left,value);
    }else if(value>N->value){
        N->right=insert(N->right,value);
    }else{
        return N;
    }
    N->height=maxValue(height(N->left),height(N->right)) + 1;
    int balance = getBalance(N);
    if(balance>1){
        if(value<N->left->value){
            return rightRotate(N);
        }else{
            N->left=leftRotate(N->left);
            return rightRotate(N);
        }
    }
    if(balance<-1){
        if(value>N->right->value){
            return leftRotate(N);
        }else{
            N->right=rightRotate(N->right);
            return leftRotate(N);
        }
    }
    return N;
}

void preOrder(node* N){
    if(N==NULL) return;
    printf("%d ", N->value);
    preOrder(N->left);
    preOrder(N->right);
}

int main(){
    node* root=NULL;
    root = insert(root,10);
    root = insert(root,20);
    root = insert(root,30);
    root = insert(root,40);
    root = insert(root,50);
    preOrder(root);
}




