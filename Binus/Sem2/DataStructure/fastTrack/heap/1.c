#include <stdio.h>

typedef struct node
{
    int num;
    struct node *left;
    struct node *right;
} node;

node numbs[100];
int size = 0;

void insert(int value)
{
    numbs[size].num = value;
    numbs[size].left = NULL;
    numbs[size].right = NULL;

    if (size > 0)
    {
        int parent_idx = (size - 1) / 2;
        if (size % 2 == 1)
        {
            numbs[parent_idx].left = &numbs[size];
        }
        else
        {
            numbs[parent_idx].right = &numbs[size];
        }
    }

    int current = size;
    while (current > 0)
    {
        int parent_idx = (current - 1) / 2;
        if (numbs[current].num < numbs[parent_idx].num)
        {
            int temp = numbs[current].num;
            numbs[current].num = numbs[parent_idx].num;
            numbs[parent_idx].num = temp;
            current = parent_idx;
        }
        else
        {
            break;
        }
    }
    size++;
}

int main()
{
    printf("Enter 10 integers:\n");
    for (int i = 0; i < 10; i++)
    {
        int val;
        // Fixed your scanf: added address-of operator '&'
        scanf("%d", &val);
        insert(val);
    }

    // Print out the root of your heap to verify
    printf("\nHeap Root: %d\n", numbs[0].num);
    if (numbs[0].left)
        printf("Left Child of Root: %d\n", numbs[0].left->num);
    if (numbs[0].right)
        printf("Right Child of Root: %d\n", numbs[0].right->num);

    return 0;
}
