#include <stdio.h>

int parent[105];

int find(int i) {
    if (parent[i] == i) {
        return i;
    }
    return parent[i] = find(parent[i]);
}

void unionSet(int u, int v) {
    int root_u = find(u);
    int root_v = find(v);
    
    if (root_u != root_v) {
        parent[root_u] = root_v;
    }
}

int main() {
    int P, R;
    
    if (scanf("%d %d", &P, &R) != 2) {
        return 0;
    }

    for (int i = 1; i <= P; i++) {
        parent[i] = i;
    }

    int hasCycle = 0;

    for (int i = 0; i < R; i++) {
        int a, b;
        scanf("%d %d", &a, &b);

        if (hasCycle) {
            continue;
        }

        int root_a = find(a);
        int root_b = find(b);

        if (root_a == root_b) {
            hasCycle = 1;
        } else {
            unionSet(a, b);
        }
    }
    
    if (hasCycle) {
        printf("CYCLE\n");
    } else {
        printf("SAFE\n");
    }

    return 0;
}