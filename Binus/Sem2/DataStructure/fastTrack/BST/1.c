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
    if(root==NULL){
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

node* search(node* root, int value){
    if(root==NULL){
        return NULL;
    }
    if(root->value==value){
        return root;
    }
    if(value<root->value){
        return search(root->left,value);
    }else{
        return search(root->right,value);
    }

}