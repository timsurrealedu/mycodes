#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Comparator function for qsort
int compare(const void *a, const void *b) {
    return (*(int *)a - *(int *)b);
}

int main() {
    // The program is expected to read a file "testdata.in" [cite: 15]
    FILE *file = fopen("testdata.in", "r");
    
    // Safety check if file exists
    if (file == NULL) {
        printf("Error: testdata.in not found.\n");
        return 1;
    }

    int T;
    // Read the number of test cases [cite: 15]
    fscanf(file, "%d", &T);

    for (int t = 1; t <= T; t++) {
        int N, M;
        // Read dimensions N and M [cite: 15]
        fscanf(file, "%d %d", &N, &M);

        int total_pixels = N * M;
        // Constraint: N, M <= 100, so max pixels is 10,000 
        // We allocate slightly more for safety.
        int pixels[10005]; 

        // Read the N lines of M integers [cite: 16]
        for (int i = 0; i < total_pixels; i++) {
            fscanf(file, "%d", &pixels[i]);
        }

        // Sort the array to find the median logic
        qsort(pixels, total_pixels, sizeof(int), compare);

        double median;
        
        // Calculate median based on total count
        if (total_pixels % 2 != 0) {
            // If odd, pick the exact middle element
            median = pixels[total_pixels / 2];
        } else {
            // If even, average the two middle elements
            int mid1 = pixels[total_pixels / 2 - 1];
            int mid2 = pixels[total_pixels / 2];
            median = (mid1 + mid2) / 2.0;
        }

        // Output format: "Case #X: Y", where Y is rounded to nearest integer 
        // standard round() function requires math.h and linking with -lm
        int result = (int)round(median);

        printf("Case #%d: %d\n", t, result);
    }

    fclose(file);
    return 0;
}