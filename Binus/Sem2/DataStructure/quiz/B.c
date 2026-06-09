#include <stdio.h>
#include <stdlib.h>

void reverse(int *start, int *end) {
    while (start < end) {
        int temp = *start;
        *start = *end;
        *end = temp;
        start++;
        end--;
    }
}

int main() {
    int n, k;
    
    if (scanf("%d %d", &n, &k) != 2) {
        return 0;
    }

    int *arr = (int *)malloc(n * sizeof(int));
    if (!arr) {
        return 1;
    }

    for (int i = 0; i < n; i++) {
        scanf("%d", arr + i);
    }

    k = k % n;

    if (k > 0) {
        reverse(arr, arr + n - 1);
        
        reverse(arr, arr + k - 1);
        
        reverse(arr + k, arr + n - 1);
    }

    for (int i = 0; i < n; i++) {
        printf("%d", *(arr + i));
        if (i < n - 1) {
            printf(" ");
        }
    }
    printf("\n");

    free(arr);
    
    return 0;
}