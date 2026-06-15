#include <stdio.h>
#include <stdlib.h>

typedef struct Node{
    int key;
    struct Node* left;
    struct Node* right;
    int height;
}Node;

int maxValue(int a, int b){
    return (a>b) ? a:b;
}

int getHeight(Node* n){
    if(n==NULL) return 0;
    return n->height;
}

int getBalance(Node* n){
    if(n==NULL) return 0;
    return getHeight(n->left)-getHeight(n->right);
}

Node* createNode(int key){
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->key=key;
    newNode->left=NULL;
    newNode->right=NULL;
    newNode->height=1;
    return newNode;
}

Node* rightRotate(Node* a){
    Node* b = a->left;
    Node* e = b->right;

    b->right=a;
    a->left=e;

    a->height = maxValue(getHeight(a->left),getHeight(a->right))+1;
    b->height = maxValue(getHeight(b->left),getHeight(b->right))+1;

    return b;
}

Node* leftRotate(Node* a){
    Node* c = a->right;
    Node* d = c->left;

    c->left=a;
    a->right=d;

    a->height=maxValue(getHeight(a->left),getHeight(a->right))+1;
    c->height=maxValue(getHeight(c->left),getHeight(c->right))+1;

    return c;
}

Node* insert(Node* n, int key){
    if(n==NULL){
        return createNode(key);
    }
    if(key<n->key){
        n->left=insert(n->left,key);
    }else if(key>n->key){
        n->right=insert(n->right,key);
    }else{
        return n;
    }

    n->height=1+maxValue(getHeight(n->left),getHeight(n->right));
    int balance = getBalance(n);
    if(balance>1&&key<n->left->key){
        return rightRotate(n);
    }if(balance<-1&&key>n->right->key){
        return leftRotate(n);
    }if(balance>1&&key>n->left->key){
        n->left=leftRotate(n->left);
        return rightRotate(n);
    }if(balance<-1&&key<n->right->key){
        n->right=rightRotate(n->right);
        return leftRotate(n);
    }
    return n;
}

Node* minValueNode(Node* n){
    Node* curr = n;
    while(curr->left!=NULL){
        curr = curr->left;
    }
    return curr;
}

Node* deleteNode(Node* root, int key){
    if(root==NULL){
        return root;
    }
    if(key<root->key){
        root->left=deleteNode(root->left,key);
    }else if(key>root->key){
        root->right=deleteNode(root->right,key);
    }
    else{
        if((root->left==NULL)||(root->right==NULL)){
            Node* temp = root->left?root->left:root->right;
            if(temp==NULL){
                temp = root;
                root = NULL;
            }else{
                *root = *temp;
            }
            free(temp);
        }
        else{
            Node* temp = minValueNode(root->right);
            root->key=temp->key;
            root->right=deleteNode(root->right,temp->key);
        }
    }
}