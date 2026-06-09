#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
    char name[30];
    int priority;
}Machine;

typedef struct{
    Machine val[50];
    int size;
}MaxHeap;

void swap(Machine *a, Machine* b){
    Machine temp = *a;
    *a = *b;
    *b = temp;
}

int getMax(MaxHeap* heap){
    if(heap->size==0){
        printf("heap is empty\n");
        return -1;
    }

    return heap->val[0].priority;
}

void insert(MaxHeap* heap, int value, char name[30]){
    int curridx = heap->size;
    strcpy(heap->val[curridx].name,name);
    heap->val[curridx].priority=value;
    heap->size++;
    while(curridx>0){
        int paridx=(curridx-1)/2;
        if(heap->val[curridx].priority>heap->val[paridx].priority){
            swap(&heap->val[curridx],&heap->val[paridx]);
            curridx=paridx;
        }
        else{
            break;
        }
    }
}

void siftDown(MaxHeap* heap, int curridx){
    while((2*curridx)+1 < heap->size){
        int leftidx = (2*curridx)+1;
        int rightidx = (2*curridx)+2;
        int largestidx = leftidx;
        if(rightidx<heap->size&&heap->val[rightidx].priority>heap->val[largestidx].priority){
            largestidx=rightidx;
        }
        if(heap->val[curridx].priority>=heap->val[largestidx].priority){
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
    printf("extracting: %s", heap->val[0].name);
    heap->val[0]=heap->val[heap->size-1];
    heap->size--;
    siftDown(heap,0);
}

// void heapify(MaxHeap* heap, int arr[], int n){
//     for(int i = 0 ; i < n ; i++){
//         heap->val[i]=arr[i];
//     }
//     heap->size=n;
//     for(int i = (n/2)-1; i>=0;i--){
//         siftDown(heap,i);
//     }
// }

void display(MaxHeap* heap){
    for(int i = 0 ; i < heap->size;i++){
        printf("%s %d ", heap->val[i].name, heap->val[i].priority);
    }
}

int main() {
    MaxHeap queue = {{}, 0}; // Inisialisasi heap kosong
    int Q;
    
    // 1. Baca jumlah perintah
    scanf("%d", &Q);
    
    // 2. Looping sebanyak Q
    for (int i = 0; i < Q; i++) {
        char command[20];
        scanf("%s", command);
        
        if (strcmp(command, "REPORT") == 0) {
            char name[26];
            int priority;
            scanf("%s %d", name, &priority);
            
            insert(&queue,priority,name);
            // Panggil fungsi insert() Anda di sini
            // Ingat untuk handle "MACHINE QUEUE FULL"
            
        } else if (strcmp(command, "REPAIR") == 0) {
            
            extractMax(&queue);
            // Panggil fungsi extractMax() Anda di sini
            // Ingat untuk handle "NO MACHINES" dan cetak "REPAIRING..."
            
        } else if (strcmp(command, "CHECK") == 0) {
            
            display(&queue);
            // Panggil fungsi display() Anda di sini
            
        }
    }
    return 0;
}