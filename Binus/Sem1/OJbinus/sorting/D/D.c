#include <stdio.h>

void merge_sort(int* a, int length);
void merge_sort_recursion(int* a, int l, int r);
void merge_sorted_arrays(int* a, int l, int m, int r);

int main(){

}

void merge_sort(int* a, int length) {
    merge_sort_recursion(a, 0, length - 1);
}

// Recursive function that divides the array
void merge_sort_recursion(int* a, int l, int r) {
    // Stop recursion when left index is >= right index
    if (l < r) {
        // Calculate the middle index
        int m = l + (r - l) / 2;

        // Recursively sort the left half
        merge_sort_recursion(a, l, m);
        
        // Recursively sort the right half
        merge_sort_recursion(a, m + 1, r);

        // Merge the two sorted halves
        merge_sorted_arrays(a, l, m, r);
    }
}

// Function to merge two sorted portions of the array
void merge_sorted_arrays(int* a, int l, int m, int r) {
    // Calculate lengths of the left and right portions
    int left_length = m - l + 1;
    int right_length = r - m;

    // Create temporary arrays to hold the data
    int temp_left[left_length];
    int temp_right[right_length];

    int i, j, k;

    // Copy data to temp_left array
    for (int i = 0; i < left_length; i++) {
        temp_left[i] = a[l + i];
    }

    // Copy data to temp_right array
    for (int i = 0; i < right_length; i++) {
        temp_right[i] = a[m + 1 + i];
    }

    // Merge the temp arrays back into the original array a[]
    // i tracks temp_left, j tracks temp_right, k tracks a[]
    for (i = 0, j = 0, k = l; k <= r; k++) {
        
        // Check if we should pick from the left array:
        // 1. If left array still has elements AND
        // 2. Either right array is empty OR left element is smaller/equal
        if ((i < left_length) &&
            (j >= right_length || temp_left[i] <= temp_right[j])) {
            
            a[k] = temp_left[i];
            i++;
        } else {
            a[k] = temp_right[j];
            j++;
        }
    }
}