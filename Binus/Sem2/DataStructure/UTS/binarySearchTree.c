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
        root=createNode(value);
        return root;
    }
    if(value<root->value){
        root->left=insert(root->left,value);
    }if(value>root->value){
        root->right=insert(root->right,value);
    }
    return root;
}

node* findMin(node* root){
    while(root->left!=NULL){
        root = root->left;
    }
    return root;
}

node* findMax(node* root){
    while(root->right!=NULL){
        root = root->right;
    }
    return root;
}

void inOrder(node* root){
    if(root!=NULL){
        inOrder(root->left);
        printf("%d ", root->value);
        inOrder(root->right);
    }
}

void preOrder(node* root){
    if(root!=NULL){
        printf("%d ",root->value);
        preOrder(root->left);
        preOrder(root->right);
    }
}

void postOrder(node* root){
    if(root!=NULL){
        postOrder(root->left);
        postOrder(root->right);
        printf("%d ", root->value);
    }
}

node* delete(node* root, int value){
    if(root==NULL){
        return NULL;
    }
    if(value<root->value){
        root->left=delete(root->left,value);
    }
    else if(value>root->value){
        root->right=delete(root->right,value);

    }
    else{
        if(root->left==NULL){
            node* temp = root->right;
            free(root);
            return temp;
        }
        if(root->right==NULL){
            node* temp = root->left;
            free(root);
            return temp;
        }
        node* temp = findMin(root->right);
        root->value=temp->value;
        root->right=delete(root->right,root->value);
    }
    return root;
}

node* search(node* root, int value){
    if(root==NULL){
        return root;
    }
    node* curr = root;
    while(curr){
        if(value==curr->value){
            return curr; 
        }
        if(value<curr->value){
            curr=curr->left;
        }
        else{
            curr = curr->right;
        }
        
    }
    return NULL; 
}

int main(){
    node* root = NULL;
    root = insert(root, 10);
    root = insert(root, 20);
    root = insert(root, 50);
    root = insert(root, 5);
    root = insert(root, 5);
    root = insert(root, 3);
    root = insert(root, 15);
    root = delete(root, 20);
    inOrder(root);
    printf("\n");
    preOrder(root);
    printf("\n");
    postOrder(root);
    if(search(root,67)!=NULL){
        printf("\nfound\n");
    }
}
