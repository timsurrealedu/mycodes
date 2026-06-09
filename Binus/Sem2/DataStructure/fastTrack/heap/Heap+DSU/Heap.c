#include <stdio.h>

int HEAP[100];
int size = 0;

void swap(int u, int v) {
    int temp = HEAP[u];
    HEAP[u] = HEAP[v];
    HEAP[v] = temp;
}

int isHigher(int u, int v) { return u > v; }

void push(int val) {
    size++;
    HEAP[size] = val;

    int cur = size;
    while (cur != 1 && isHigher(HEAP[cur], HEAP[cur / 2])) {
        swap(cur, cur / 2);
        cur /= 2;
    }
}

void pop() {
    HEAP[1] = HEAP[size];
    size--;

    int cur = 1;
    while (cur * 2 <= size) {
        int maks = HEAP[cur];
        int idx = cur;
        if (cur * 2 <= size && isHigher(HEAP[cur * 2], maks)) {
            maks = HEAP[cur * 2];
            idx = cur * 2;
        }
        if (cur * 2 + 1 <= size && isHigher(HEAP[cur * 2 + 1], maks)) {
            maks = HEAP[cur * 2 + 1];
            idx = cur * 2 + 1;
        }
        if (cur == idx)
            break;
        swap(cur, idx);
        cur = idx;
    }
}

int top() { return HEAP[1]; }

int main() {
    push(5);
    push(3);
    push(7);
    push(2);
    push(1);
    push(2);
    push(7);
    push(5);
    push(4);

    while (size != 0) {
        printf("%d ", top());
        pop();
    }
    return 0;
}
