#include <stdio.h>
#include <stdlib.h>

typedef struct node{
    int value;
    struct node* left;
    struct node* right;
}node;

node* createNode(int value){
    node* newNode = (node*)malloc(sizeof(node));
    newNode->value=value;
    newNode->left=NULL;
    newNode->right=NULL;
    return newNode;
}

node* insert(node* root, int value){
    if(root == NULL){
        return createNode(value);
    }
    if(value<root->value){
        root->left=insert(root->left,value);
    }
    if(value>root->value){
        root->right=insert(root->right,value);
    }
    return root;
}

void traversePrint(node* root){
    if(root!=NULL){
        traversePrint(root->left);
        printf("%d ", root->value);
        traversePrint(root->right);
    }
}

int main(){
    node* root = NULL;
    root = insert(root,10);
    root = insert(root,15);
    root = insert(root,7);
    traversePrint(root);
}