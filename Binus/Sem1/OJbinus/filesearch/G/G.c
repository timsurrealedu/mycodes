#include <stdio.h>
#include <string.h>

int main() {
    // Open the file testdata.in for reading
    FILE *fp = fopen("testdata.in", "r");
    
    if (fp == NULL) {
        printf("Error: testdata.in not found.\n");
        return 1;
    }

    int T;
    // Read number of test cases
    fscanf(fp, "%d", &T);

    for (int t = 1; t <= T; t++) {
        int N, A, B;
        // Read N (total duration), A (min duration), B (max duration)
        fscanf(fp, "%d %d %d", &N, &A, &B);

        // Buffer to store the binary string. 
        // Size 10005 covers the constraint N <= 10000 plus safety/null-terminator.
        char S[10005];
        fscanf(fp, "%s", S);

        int lightningCount = 0;
        int currentDuration = 0;

        for (int i = 0; i < N; i++) {
            if (S[i] == '1') {
                // Sound continues, increment duration
                currentDuration++;
            } else {
                // Sound stopped (we hit a '0')
                // Check if the previous sound block was valid lightning
                if (currentDuration >= A && currentDuration <= B) {
                    lightningCount++;
                }
                // Reset duration for the next block
                currentDuration = 0;
            }
        }

        // Edge Case: If the string ends with '1's, the loop finishes 
        // without hitting a '0' to trigger the check. We must check now.
        if (currentDuration >= A && currentDuration <= B) {
            lightningCount++;
        }

        // Output format: Case #X: Y
        printf("Case #%d: %d\n", t, lightningCount);
    }

    fclose(fp);
    return 0;
}