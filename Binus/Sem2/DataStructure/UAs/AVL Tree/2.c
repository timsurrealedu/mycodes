#include <stdio.h>
#include <stdlib.h>

typedef struct node{
    int key;
    int height;
    struct node* left;
    struct node* right;
}node;

node* createNode(int key){
    node* newNode = (node*)malloc(sizeof(node));
    newNode->height=1;
    newNode->key=key;
    newNode->left=NULL;
    newNode->right=NULL;
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
    if(n==NULL) return 0;
    return getHeight(n->left)-getHeight(n->right);
}

node* minValueNode(node* n){
    if(n==NULL) return NULL;
    node* temp = n;
    while(temp->left!=NULL){
        temp=temp->left;
    }

    return temp;
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
    if(key>n->key){
        n->right=insert(n->right,key);
    }else if(key<n->key){
        n->left=insert(n->left,key);
    }
    else{
        return n;
    }
    n->height=1+maxValue(getHeight(n->left),getHeight(n->right));
    int balance = getBalance(n);
    if(balance>1&&getBalance(n->left)>=0){
        return rightRotate(n);
    }
    if(balance>1&&getBalance(n->left)<0){
        n->left=leftRotate(n->left);
        return rightRotate(n);
    }
    if(balance<-1&&getBalance(n->right)<=0){
        return leftRotate(n);
    }
    if(balance<-1&&getBalance(n->right)>0){
        n->right=rightRotate(n->right);
        return leftRotate(n);
    }
    return n;
}

node* delete(node* n, int key){
    if(n==NULL)return NULL;
    if(key>n->key){
        n->right=delete(n->right,key);
    }
    else if(key<n->key){
        n->left=delete(n->left,key);
    }else{
        if(n->left==NULL || n->right==NULL){
            node* temp = n->left ? n->left : n->right;
            if(temp == NULL){
                temp = n;
                n = NULL;
            }else{
                *n = *temp;
            }
            free(temp);
        }else{
            node* temp = minValueNode(n->right);
            n->key=temp->key;
            n->right=delete(n->right,temp->key);
        }
    }
    if(n==NULL)return NULL;
    n->height=1+maxValue(getHeight(n->left),getHeight(n->right));
    int balance = getBalance(n);
    if(balance>1&&getBalance(n->left)>=0){
        return rightRotate(n);
    }if(balance>1&&getBalance(n->left)<0){
        n->left=leftRotate(n->left);
        return rightRotate(n);
    }
    if(balance<-1&&getBalance(n->right)<=0){
        return leftRotate(n);
    }if(balance<-1&&getBalance(n->right)>0){
        n->right=rightRotate(n->right);
        return leftRotate(n);
    }
    return n;
}

void preOrder(node* n){
    if(n!=NULL){
        printf("%d ",n->key);
        preOrder(n->left);
        preOrder(n->right);
    }
}

int main() {
    node *root = NULL;

    printf("--- Simulasi AVL Tree ---\n\n");

    // Simulasi Insert: Memicu LL, RR, LR, RL
    int arr[] = {50, 30, 20, 40, 70, 60, 80};
    int n = sizeof(arr)/sizeof(arr[0]);

    for(int i = 0; i < n; i++) {
        root = insert(root, arr[i]);
        printf("Insert %d selesai.\n", arr[i]);
    }

    printf("\nPohon setelah semua insert (Pre-Order):\n");
    preOrder(root);
    printf("\n");

    // Simulasi Delete
    printf("\nMenghapus node 20...\n");
    root = delete(root, 20);

    printf("Pohon setelah 20 dihapus (Pre-Order):\n");
    preOrder(root);
    printf("\n");

    return 0;
}
