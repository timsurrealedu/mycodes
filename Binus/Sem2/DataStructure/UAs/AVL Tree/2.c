#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <wchar.h>

typedef struct node {
    int key;
    struct node *left;
    struct node *right;
    int height;
} node;

int maxValue(int a, int b) {
    return (a>b)?a:b;
}

int getHeight(node *n) {
    if (n == NULL)
        return 0;
    return n->height;
}

int getBalance(node *n) {
    if (n == NULL)
        return 0;
    return getHeight(n->left) - getHeight(n->right);
}

node *createNode(int key) {
    node *newNode = (node *)malloc(sizeof(node));
    newNode->key = key;
    newNode->height = 1;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

node *rightRotate(node *a) {
    node *b = a->left;
    node *e = b->right;

    b->right = a;
    a->left = e;

    a->height = maxValue(getHeight(a->left), getHeight(a->right)) + 1;
    b->height = maxValue(getHeight(b->left), getHeight(b->right)) + 1;

    return b;
}

node *leftRotate(node *a) {
    node *c = a->right;
    node *d = c->left;

    c->left = a;
    a->right = d;

    a->height = 1 + maxValue(getHeight(a->left), getHeight(a->right));
    c->height = 1 + maxValue(getHeight(c->left), getHeight(c->right));
    return c;
}

node* insert(node *n, int key) {
    if (n == NULL) {
        return createNode(key);
    }
    if (key > n->key) {
        n->right=insert(n->right,key);
    } else if (key < n->key) {
        n->left=insert(n->left,key);
    } else {
        return n;
    }
    n->height = 1 + maxValue(getHeight(n->left), getHeight(n->right));
    int balance = getBalance(n);
    if (balance > 1 && key < n->left->key) {
        return rightRotate(n);
    }
    if (balance < -1 && key > n->right->key) {
        return leftRotate(n);
    }
    if (balance > 1 && key > n->left->key) {
        n->left = leftRotate(n->left);
        return rightRotate(n);
    }
    if (balance < -1 && key < n->right->key) {
        n->right = rightRotate(n->right);
        return leftRotate(n);
    }
    return n;
}

node *minValueNode(node *n) {
    if (n == NULL)
        return NULL;
    node *temp = n;
    while (temp->left != NULL) {
        temp = temp->left;
    }
    return temp;
}

node *delete(node *n, int key) {
    if (n == NULL) {
        return n;
    }
    if (key < n->key) {
        n->left=delete(n->left,key);
    } else if (key > n->key) {
        n->right=delete(n->right,key);
    } else {
        if ((n->left == NULL) || (n->right == NULL)) {
            node* temp = n->left ? n->left : n->right;
            if (temp == NULL) {
                temp = n;
                n=NULL;
            } else {
                *n = *temp;
            }
            free(temp);
        } else {
            node *temp = minValueNode(n->right);
            n->key = temp->key;
            n->right=delete(n->right,temp->key);
        }
    }
    if (n == NULL) {
        return n;
    }
    n->height = 1 + maxValue(getHeight(n->left), getHeight(n->right));
    int balance = getBalance(n);
    if (balance > 1 && getBalance(n->left) >= 0) {
        return rightRotate(n);
    }
    if (balance < -1 && getBalance(n->right) <= 0) {

    }
}
