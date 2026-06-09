#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Data {
    int semester;
    char nama[30];
};

struct Data HEAP[100];
int size = 0;

void swap(int u, int v) {
    struct Data temp = HEAP[u];
    HEAP[u] = HEAP[v];
    HEAP[v] = temp;
}

int isHigher(struct Data u, struct Data v) {
    if (u.semester < v.semester)
        return 1;
    if (u.semester > v.semester)
        return 0;
    return strcmp(u.nama, v.nama) == -1;
}

void push(struct Data val) {
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
        struct Data maks = HEAP[cur];
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

struct Data top() { return HEAP[1]; }

int main() {
    int N, i;
    scanf("%d", &N);
    for (i = 0; i < N; i++) {
        struct Data val;
        scanf("%d %s", &val.semester, val.nama);
        push(val);
    }
    while (size != 0) {
        struct Data cur = top();
        printf("%d %s\n", cur.semester, cur.nama);
        pop();
    }
    return 0;
}
