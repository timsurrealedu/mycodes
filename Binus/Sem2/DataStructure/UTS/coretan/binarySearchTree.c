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
    }else if(value>root->value){
        root->right=insert(root->right,value);
    }
    return root;
}

node* search(node* root, int value){
    if(root==NULL||root->value==value){
        return root;
    }
    node* curr = root;
    while(curr){
        if(value==curr->value){
            return curr;
        }
        if(value<curr->value){
            curr=curr->left;
        }else{
            curr=curr->right;
        }
    }
    return NULL;
}

void inOrder(node* root){
    if(root==NULL){
        return;
    }
    inOrder(root->left);
    printf("%d ",root->value);
    inOrder(root->right);
}

void preOrder(node* root){
    if(root==NULL){
        return;
    }
    printf("%d ", root->value);
    preOrder(root->left);
    preOrder(root->right);
}

void postOrder(node* root){
    if(root==NULL){
        return;
    }
    postOrder(root->left);
    postOrder(root->right);
    printf("%d ",root->value);

}

node* findMin(node* root){
    if(root==NULL){
        return root;
    }
    node* curr = root;
    while(curr->left){
        curr=curr->left;
    }
    return curr;
}

node* delete(node* root, int value){
    if(root==NULL){
        return root;
    }
    if(value<root->value){
        root->left=delete(root->left,value);
    }else if(value>root->value){
        root->right=delete(root->right,value);
    }else{
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
        root->right=delete(root->right,temp->value);
    }
    return root;
}



node* clear(node* root){
    if(root==NULL){
        return root;
    }
    root->left=clear(root->left);
    root->right=clear(root->right);
    free(root);
    return NULL;
}

int main(){
    node* root = NULL;
    root = insert(root,10);
    root = insert(root, 50);
    root = insert(root, 5);
    root = delete(root, 10);
    if(search(root, 5)!=NULL){
        printf("ads");
    }
    root = clear(root);
    inOrder(root);
}