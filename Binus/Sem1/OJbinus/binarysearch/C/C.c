#include <stdio.h>

// Function to find the largest index where prefix[index] <= M
int findIndex(long long prefix[], int n, long long M) {
    int left = 0;          // FIX 1: Initialize left to 0
    int right = n - 1;
    int answer = -1;       // Default -1 if no prefix <= M

    while (left <= right) {
        int mid = left + (right - left) / 2; // Safer way to calculate mid

        // FIX 3: Change '<' to '<=' because exact matches are allowed
        if (prefix[mid] <= M) {
            answer = mid;
            left = mid + 1; // Try to find a larger index (move right)
        } else {
            right = mid - 1; // Sum is too big, need smaller index (move left)
        }
    }
    return answer;
}

int main() {
    int N;
    if (scanf("%d", &N) != 1) return 0;

    long long A[100005];
    long long prefix[100005];

    for (int i = 0; i < N; i++) {
        scanf("%lld", &A[i]);
    }

    // FIX 2: Correct Prefix Sum Logic
    prefix[0] = A[0];
    for (int i = 1; i < N; i++) { // Start loop at 1 to avoid accessing index -1
        prefix[i] = prefix[i - 1] + A[i];
    }

    int Q;
    scanf("%d", &Q);

    for (int t = 1; t <= Q; t++) {
        long long M;
        scanf("%lld", &M);

        int idx = findIndex(prefix, N, M);

        if (idx == -1) {
            printf("Case #%d: -1\n", t);
        } else {
            // Output asks for 1-based index, so we print idx + 1
            printf("Case #%d: %d\n", t, idx + 1);
        }
    }

    return 0;
}