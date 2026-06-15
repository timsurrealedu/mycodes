#include <stdio.h>
#include <stdlib.h>

typedef struct{
    int val[50];
    int size;
}MaxHeap;

void swap(int *a, int*b){
    int temp = *a;
    *a = *b;
    *b = temp;
}

int getMax(MaxHeap* heap){
    if(heap->size==0){
        return -1;
    }
    return heap->val[0];
}

void insert(MaxHeap* heap, int value){
    int curridx = heap->size;
    heap->val[curridx]=value;
    heap->size++;
    while(curridx>0){
        
    }
}