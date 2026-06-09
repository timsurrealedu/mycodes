#include <stdio.h>
#include <string.h>

typedef struct {
    char c;
    int freq;
} Node;

Node heap[26];
int heapSize = 0;

void swap(Node *a, Node *b) {
    Node temp = *a;
    *a = *b;
    *b = temp;
}

int hasHigherPriority(Node a, Node b) {
    if (a.freq > b.freq) {
        return 1;
    }
    if (a.freq == b.freq && a.c > b.c) {
        return 1;
    }
    return 0;
}

void upheap(int idx) {
    if (idx == 0) return; 
    
    int parent = (idx - 1) / 2;
    
    if (hasHigherPriority(heap[idx], heap[parent])) {
        swap(&heap[idx], &heap[parent]);
        upheap(parent);
    }
}

void downheap(int idx) {
    int largest = idx;
    int left = 2 * idx + 1;
    int right = 2 * idx + 2;

    if (left < heapSize && hasHigherPriority(heap[left], heap[largest])) {
        largest = left;
    }
    if (right < heapSize && hasHigherPriority(heap[right], heap[largest])) {
        largest = right;
    }

    if (largest != idx) {
        swap(&heap[idx], &heap[largest]);
        downheap(largest);
    }
}

void insertHeap(char c, int freq) {
    heap[heapSize].c = c;
    heap[heapSize].freq = freq;
    upheap(heapSize);
    heapSize++;
}

Node extractMax() {
    Node maxNode = heap[0];
    
    heap[0] = heap[heapSize - 1];
    heapSize--;
    
    downheap(0);
    
    return maxNode;
}

int main() {
    int k;
    char s[105];

    if (scanf("%d", &k) != 1) return 0;
    if (scanf("%s", s) != 1) return 0;

    int freq[26] = {0};
    int len = strlen(s);

    for (int i = 0; i < len; i++) {
        if (s[i] >= 'A' && s[i] <= 'Z') {
            freq[s[i] - 'A']++;
        }
    }

    for (int i = 0; i < 26; i++) {
        if (freq[i] > 0) {
            insertHeap('A' + i, freq[i]);
        }
    }

    int count = 0;
    while (count < k && heapSize > 0) {
        Node top = extractMax();
        printf("%c %d\n", top.c, top.freq);
        count++;
    }

    return 0;
}