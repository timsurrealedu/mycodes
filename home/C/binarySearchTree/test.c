#include <stdio.h>
#include <stdlib.h>

typedef struct node{
    int value;
    struct node* left;
    struct node* right;
}node;

node* root = NULL;

node* createNode(int value){
    node* newNode=(node*)malloc(sizeof(node));
    newNode->value=value;
    newNode->right=NULL;
    newNode->left=NULL;
    return newNode;
}

void push(int value){
    if(root==NULL){
        root=createNode(value);
        return;
    }
    while(1){
        if(root->value>value){
            node* curr = root;
            if(curr->left==NULL){
                curr->left=createNode(value);
                return;
            }
            curr = curr->left;
        }
        else if(root->value<value){
            node* curr = root;
            if(curr->right==NULL){
                curr->right=createNode(value);
                return;
            }
            curr = curr->right;
        }
        else{
            printf("already exists\n");
            return;
        }
    }
}

node* findMin(node* thenode){
    while(thenode->left!=NULL){
        thenode=thenode->left;
    }
    return thenode;
}

void pop(int value){

}

int main(){
    printf("aasd\n");
    return 0;
}