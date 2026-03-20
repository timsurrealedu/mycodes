#include <stdio.h>

#define MAXN 1000

int N;
int tree[MAXN];
int leafSums[MAXN];
int leafCount;

// Recursive DFS
void dfs(int idx, int sum) {
    if (idx >= N) return; // out of bounds
    sum += tree[idx];

    int left = 2*idx + 1;
    int right = 2*idx + 2;

    if (left >= N && right >= N) {
        // leaf node
        leafSums[leafCount++] = sum;
        return;
    }

    if (left < N) dfs(left, sum);
    if (right < N) dfs(right, sum);
}

int main() {
    int T;
    scanf("%d", &T);

    for (int t = 1; t <= T; t++) {
        scanf("%d", &N);
        for (int i = 0; i < N; i++) {
            scanf("%d", &tree[i]);
        }

        leafCount = 0;
        dfs(0, 0);

        printf("Case #%d:\n", t);
        for (int i = 0; i < leafCount; i++) {
            printf("%d ", leafSums[i]);
        }
        printf("\n");
    }

    return 0;
}
