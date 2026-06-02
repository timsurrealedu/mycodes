#include <stdio.h>

struct maxheap
{
    int data[50];
    int size;
};

void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

void insert(maxheap *heap, int val)
{
    int curridx = heap->size;
    heap->data[curridx] = val;
    heap->size++;
    while (curridx > 0)
    {
        int parentidx = (curridx - 1) / 2;
        if (heap->data[curridx] > heap->data[parentidx])
        {
            swap(&heap->data[curridx], &heap->data[parentidx]);
            curridx = parentidx;
        }
        else
        {
            break;
        }
    }
}

void printheap(maxheap heap)
{
    for (int i = 0; i < heap.size; i++)
    {
        printf("%d ", heap.data[i]);
    }
    printf("\n");
}

int main()
{
    maxheap heap;
    heap.size = 0;
    insert(&heap, 10);
    insert(&heap, 100);
    insert(&heap, 50);
    insert(&heap, 20);
    insert(&heap, 1000);
    printheap(heap);
}