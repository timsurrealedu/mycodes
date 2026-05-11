#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
    int key;
    struct node *left;
    struct node *right;
    int height;
} node;

int max(int a, int b)
{
    return (a > b) ? a : b;
}

int height(node *n)
{
    if (n == NULL)
    {
        return 0;
    }
    return n->height;
}
