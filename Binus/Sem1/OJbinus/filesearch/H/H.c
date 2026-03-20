#include <stdio.h>
#include <stdlib.h>

// Comparison function for qsort to sort long long integers in ascending order
int compare(const void *a, const void *b) {
    long long num1 = *(long long *)a;
    long long num2 = *(long long *)b;
    
    if (num1 < num2) return -1;
    if (num1 > num2) return 1;
    return 0;
}

int main() {
    int N;
    // Read N from standard input
    // The problem statement implies a single test case structure per run
    // based on "The input consists of three lines" [cite: 121]
    if (scanf("%d", &N) != 1) {
        return 0;
    }

    // Allocate memory for boss powers. 
    // Using a slightly larger array for safety. N <= 100 [cite: 128]
    long long bossPowers[105]; 
    
    // Read the N boss powers
    for (int i = 0; i < N; i++) {
        scanf("%lld", &bossPowers[i]);
    }

    long long Y;
    // Read Jojo's initial power
    scanf("%lld", &Y);

    // Sort the boss powers from smallest to largest
    // Logic: Defeating weaker bosses first preserves Y for as long as possible.
    qsort(bossPowers, N, sizeof(long long), compare);

    int count = 0;

    // Iterate through the sorted missions
    for (int i = 0; i < N; i++) {
        // If Jojo has enough power to defeat the current boss
        if (Y >= bossPowers[i]) {
            Y -= bossPowers[i]; // Decrease Jojo's power
            count++;            // Increment mission count
        } else {
            // Since the array is sorted, if Jojo can't defeat this boss,
            // he cannot defeat any subsequent (stronger) bosses.
            break;
        }
    }

    // Output the result
    printf("%d\n", count);

    return 0;
}