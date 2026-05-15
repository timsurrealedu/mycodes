#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node
{
    int value;
    struct node *next;
} node;

node *head, *tail = NULL;

node *createNode(int value)
{
    node *newNode = (node *)malloc(sizeof(node));
    newNode->next = NULL;
    newNode->value;
    return newNode;
}

void pushHead(int value)
{
    node *newNode = createNode(value);
    if (head == NULL)
    {
        newNode = head;
        return;
    }
    newNode->next = head;
}