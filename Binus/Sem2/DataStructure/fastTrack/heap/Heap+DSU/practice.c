#include <stdio.h>
#include <stdlib.h>

typedef struct{
    int val[50];
    int size;
}MaxHeap;

void swap(int* a, int* b){
    int temp = *a;
    *a = *b;
    *b = temp;
}

int getMax(MaxHeap* heap){
    if(heap->size==0){
        printf("heap is empty\n");
        return -1;
    }
    return heap->val[0];
}

void insert(MaxHeap* heap, int value){
    int curridx = heap->size;
    heap->val[curridx]=value;
    heap->size++;
    while(curridx>0){
        int paridx = (curridx-1)/2;
        if(heap->val[curridx]>heap->val[paridx]){
            swap(&heap->val[curridx],&heap->val[paridx]);
            curridx=paridx;
        }
        else{
            break;
        }
    }
}

void siftDown(MaxHeap* heap, int curridx){
    while((2*curridx)+1<heap->size){
        int leftidx = (2*curridx)+1;
        int rightidx = (2*curridx)+2;
        int largestidx = leftidx;

        if(rightidx<heap->size&&heap->val[rightidx]>heap->val[largestidx]){
            largestidx=rightidx;
        }if(heap->val[curridx]>=heap->val[largestidx]){
            break;
        }
        swap(&heap->val[curridx],&heap->val[largestidx]);
        curridx=largestidx;
    }

}

void extractMax(MaxHeap* heap){
    if(heap->size==0){
        printf("heap is empty\n");
        return;
    }
    printf("extracted: %d",heap->val[0]);
    heap->val[0]=heap->val[heap->size-1];
    heap->size--;
    siftDown(heap,0);
}

void heapify(MaxHeap* heap, int arr[], int n){
    for(int i = 0 ; i < n ; i++){
        heap->val[i]=arr[i];
    }
    heap->size=n;
    for(int i = (n/2)-1;i>=0;i--){
        siftDown(heap,i);
    }
}

void display(MaxHeap* heap){
    printf("Heap: ");
    for(int i = 0 ; i < heap->size;i++){
        printf("%d ", heap->val[i]);
    }
    printf("\n");
}

int main(){
    MaxHeap heap = {{0},0};

    int arr[]={3,1,6,5,2,4};

    heapify(&heap,arr,6);
    printf("setelah heapify:");
    display(&heap);
}