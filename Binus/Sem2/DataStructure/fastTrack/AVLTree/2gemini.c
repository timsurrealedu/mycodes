#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
    int value;
    struct node *left;
    struct node *right;
    int height;
} node;

node *createNode(int value)
{
    node *newNode = (node *)malloc(sizeof(node));
    newNode->value = value;
    newNode->height = 1;
    newNode->right = NULL;
    newNode->left = NULL;
    return newNode;
}

int height(node *N)
{
    if (N == NULL)
    {
        return 0;
    }
    return N->height;
}

int max(int a, int b)
{
    return (a > b) ? a : b;
}

node *rightRotate(node *y)
{
    node *x = y->left;
    node *T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;

    return x;
}

struct node *leftRotate(node *x)
{
    node *y = x->right;
    node *T2 = y->left;

    y->left = x;
    x->right = T2;

    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;

    return y;
}

int getBalance(node *N)
{
    if (N == NULL)
    {
        return 0;
    }
    return height(N->left) - height(N->right);
}

node *insert(node *node, int value)
{
    if (node == NULL)
    {
        return createNode(value);
    }
    if (value < node->value)
    {
        node->left = insert(node->left, value);
    }
    else if (value > node->value)
    {
        node->right = insert(node->right, value);
    }
    else
    {
        return node;
    }

    node->height = 1 + max(height(node->left), height(node->right));
    int balance = getBalance(node);
    if (balance > 1 && value < node->left->value)
    {
        return rightRotate(node);
    }
    if (balance < -1 && value > node->right->value)
    {
        return leftRotate(node);
    }
    if (balance > 1 && value > node->left->value)
    {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }
    if (balance < -1 && value < node->right->value)
    {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    return node;
}

void preOrder(node *root)
{
    if (root != NULL)
    {
        printf("%d ", root->value);
        preOrder(root->left);
        preOrder(root->right);
    }
}

int main()
{
    node *root = NULL;
    root = insert(root, 10);
    root = insert(root, 20);
    root = insert(root, 30);
    root = insert(root, 40);
    root = insert(root, 50);
    root = insert(root, 25);

    printf("preorder traversal is: \n");
    preOrder(root);
}