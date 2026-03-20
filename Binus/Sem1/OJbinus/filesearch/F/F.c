#include <stdio.h>
#include <stdlib.h> // For abs() function

int main() {
    // Open the file testdata.in for reading as required
    FILE *fp = fopen("testdata.in", "r");
    
    if (fp == NULL) {
        printf("Error: testdata.in not found.\n");
        return 1;
    }

    int T;
    // Read number of test cases
    if (fscanf(fp, "%d", &T) != 1) {
        fclose(fp);
        return 0;
    }

    for (int t = 1; t <= T; t++) {
        int N;
        // Read number of stacks
        fscanf(fp, "%d", &N);

        int blocks[105]; // Array to store stack heights (N <= 100)
        long long totalBlocks = 0;

        // Read stack heights
        for (int i = 0; i < N; i++) {
            fscanf(fp, "%d", &blocks[i]);
            totalBlocks += blocks[i];
        }

        // --- Calculate Area ---
        // Area = Total blocks * (2 * 2)
        long long area = totalBlocks * 4;

        // --- Calculate Perimeter ---
        long long perimeter = 0;

        // 1. Horizontal Perimeter (Top + Bottom)
        // Each stack has a width of 2.
        // Bottom length = N * 2
        // Top length sum = N * 2
        perimeter += (long long)N * 2 * 2;

        // 2. Vertical Perimeter
        // Calculate the exposed vertical sides by comparing adjacent stacks.
        // We start comparing with ground level (height 0).
        int currentHeight = 0;
        int previousHeight = 0;

        for (int i = 0; i < N; i++) {
            currentHeight = blocks[i];
            
            // Calculate difference between current stack and previous stack
            // Multiply by 2 because each block height is 2
            perimeter += abs(currentHeight - previousHeight) * 2;
            
            previousHeight = currentHeight;
        }

        // Add the final drop from the last stack to the ground (height 0)
        perimeter += abs(0 - previousHeight) * 2;

        // Output format: Case #X: Perimeter Area
        printf("Case #%d: %lld %lld\n", t, perimeter, area);
    }

    fclose(fp);
    return 0;
}