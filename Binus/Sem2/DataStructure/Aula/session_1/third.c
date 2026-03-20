#include <stdio.h>

int main(){
    int A[5] = {3, 2, 5, 1, 4};
    printf("%d %d\n", &A[0], A);
    printf("%d %d\n", A[0], *A);
    printf("%d %d\n", A[1], *(A+1));
    printf("%d %d\n", 1[A], *(1+A));
}
