#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int HEAP[100];
int size = 0;

void swap(int u, int v) {
    int temp = HEAP[u];
    HEAP[u] = HEAP[v];
    HEAP[v] = temp;
}

int isHigher(int u, int v) { return u > v; }
