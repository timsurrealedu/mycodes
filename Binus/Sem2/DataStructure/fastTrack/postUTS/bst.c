#include <stdio.h>
#include <stdlib.h>

typedef struct Node
{
    int data;
    struct Node *left;
    struct Node *right;
} Node;

Node *newNode(int data)
{
    Node *node = (Node *)malloc(sizeof(Node));
    node->data = data;
    node->left = NULL;
    node->right = NULL;
    return node;
}

Node *insert(Node *root, int data)
{
    if (root == NULL)
        return newNode(data);
    if (data < root->data)
        return insert(root->left, data);
    if (data > root->data)
        return insert(root->right, data);
    return root;
}

Node *search(Node *root, int data)
{
    if (root == NULL || root->data == data)
        return root;
    if (data < root->data)
        return search(root->left, data);
    if (data > root->data)
        return search(root->right, data);
}

Node *minNode(Node *root)
{
    while (root->left != NULL)
    {
        root = root->left;
    }
    return root;
}

Node *delete(Node *root, int data)
{
    if (root == NULL)
        return root;
    if (data < root->data)
        return delete(root->left, data);
    if (data > root->data)
        return delete(root->right, data);
}