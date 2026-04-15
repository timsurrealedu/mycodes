// #include <stdio.h>
// #include <stdlib.h>

// typedef struct node{
//     int value;
//     struct node* left;
//     struct node* right;
// }node;

// node* createNode(int value){
//     node* newNode = (node*)malloc(sizeof(node));
//     newNode->value=value;
//     newNode->left=NULL;
//     newNode->right=NULL;
//     return newNode;
// }

// node* insertNode(node* root, int value){
//     if(root == NULL){
//         root = createNode(value);
//         return root;
//     }
//     if(value<root->value){
//         root->left=insertNode(root->left,value);
//     }if(value>root->value){
//         root->right=insertNode(root->right,value);
//     }
//     return root;
// }

// node* findMin(node* root){
//     while(root->left!=NULL){
//         root = root->left;
//     }
//     return root;
// }

// node* findMax(node* root){
//     while(root->right!=NULL){
//         root = root->right;
//     }
//     return root;
// }

// node* deleteNode(node* root, int value){
//     if(root == NULL){
//         return root;
//     }
//     if(value<root->value){
//         root->left=deleteNode(root->left,value);
//     }else if(value>root->value){
//         root->right=deleteNode(root->right,value);
//     }
//     else{
//         if(root->left==NULL){
//             node* temp = root->right;
//             free(root);
//             return temp;
//         }
//         else if(root->right==NULL){
//             node* temp = root->left;
//             free(root);
//             return temp;
//         }
//         node* temp = findMin(root->right);
//         root->value = temp->value;
//         root->right = deleteNode(root->right, temp->value);
//     }
//     return root;
   
// }

// void* traversePrint(node* root){
//     if(root!=NULL){
//         traversePrint(root->left);
//         printf("%d ", root->value);
//         traversePrint(root->right);
//     }
    
// }

// void freeTree(node* root){
//     if(root!=NULL){
//         freeTree(root->left);
//         freeTree(root->right);
//         free(root);
//     }
// }


// int main(){
//     node* root = NULL;
//     root = insertNode(root, 10);
//     root = insertNode(root, 5);
//     root = insertNode(root, 1);
//     root = insertNode(root, 20);
//     traversePrint(root);
//     printf("\n");
//     root = deleteNode(root, 5);
//     traversePrint(root);
//     freeTree(root);
// }


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

void traversePrint(node* root){
    if(root!=NULL){
        traversePrint(root->left);
        printf("%d ", root->value);
        traversePrint(root->right);
    }
}

int main(){
    node* root = NULL;
    root = insert(root, 10);
    root = insert(root,1);
    root = insert(root,33);
    traversePrint(root);

}