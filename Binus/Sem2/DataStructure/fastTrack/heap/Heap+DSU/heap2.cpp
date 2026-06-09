#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int val[50];
    int size;
}MaxHeap;

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// ─── PEEK ───────────────────────────────────────────────
int getMax(MaxHeap* heap) {
    if (heap->size == 0) {
        printf("Heap kosong!\n");
        return -1;
    }
    return heap->val[0];
}

// ─── INSERT ─────────────────────────────────────────────
void insert(MaxHeap* heap, int newvalue) {
    int curridx = heap->size;
    heap->val[curridx] = newvalue;
    heap->size++;
    while (curridx > 0) {
        int paridx = (curridx - 1) / 2;
        if (heap->val[curridx] > heap->val[paridx]) {
            swap(&heap->val[curridx], &heap->val[paridx]);
            curridx = paridx;
        } else {
            break;
        }
    }
}

// ─── SIFT DOWN (helper untuk extractMax & delete) ───────
void siftDown(MaxHeap* heap, int curridx) {
    while ((2 * curridx) + 1 < heap->size) {
        int leftidx  = (2 * curridx) + 1;
        int rightidx = (2 * curridx) + 2;
        int largestidx = leftidx;

        // ✅ Cek INDEX bukan VALUE
        if (rightidx < heap->size && heap->val[rightidx] > heap->val[largestidx]) {
            largestidx = rightidx;
        }
        if (heap->val[curridx] >= heap->val[largestidx]) {
            break;
        }
        swap(&heap->val[curridx], &heap->val[largestidx]);
        curridx = largestidx;
    }
}

// ─── EXTRACT MAX ─────────────────────────────────────────
void extractMax(MaxHeap* heap) {
    if (heap->size == 0) {
        printf("Heap kosong!\n");
        return;
    }
    printf("Extracted: %d\n", heap->val[0]);
    heap->val[0] = heap->val[heap->size - 1];
    heap->size--;
    siftDown(heap, 0);
}

// ─── DELETE (node di index tertentu) ─────────────────────
void deleteNode(MaxHeap* heap, int idx) {
    if (idx >= heap->size) {
        printf("Index tidak valid!\n");
        return;
    }
    // Ganti dengan nilai sangat besar lalu bubble up ke root
    heap->val[idx] = heap->val[0] + 1;
    int curridx = idx;
    while (curridx > 0) {
        int paridx = (curridx - 1) / 2;
        if (heap->val[curridx] > heap->val[paridx]) {
            swap(&heap->val[curridx], &heap->val[paridx]);
            curridx = paridx;
        } else break;
    }
    // Sekarang node ada di root, lakukan extractMax
    extractMax(heap);
}

// ─── HEAPIFY (build heap dari array biasa) ───────────────
void heapify(MaxHeap* heap, int arr[], int n) {
    for (int i = 0; i < n; i++) {
        heap->val[i] = arr[i];
    }
    heap->size = n;

    // Mulai dari node non-leaf terakhir, siftDown ke bawah → O(n)
    for (int i = (n / 2) - 1; i >= 0; i--) {
        siftDown(heap, i);
    }
}

// ─── DISPLAY ─────────────────────────────────────────────
void display(MaxHeap* heap) {
    printf("Heap: ");
    for (int i = 0; i < heap->size; i++) {
        printf("%d ", heap->val[i]);
    }
    printf("\n");
}

// ─── MAIN ────────────────────────────────────────────────
int main() {
    MaxHeap heap = {{0}, 0};

    // Test Heapify
    int arr[] = {3, 1, 6, 5, 2, 4};
    heapify(&heap, arr, 6);
    printf("Setelah heapify: ");
    display(&heap);

    // Test Insert
    insert(&heap, 10);
    printf("Setelah insert 10: ");
    display(&heap);

    // Test GetMax
    printf("Max saat ini: %d\n", getMax(&heap));

    // Test Delete index 2
    deleteNode(&heap, 2);
    printf("Setelah delete index 2: ");
    display(&heap);

    // Test Extract Max
    extractMax(&heap);
    printf("Setelah extractMax: ");
    display(&heap);

    return 0;
}
