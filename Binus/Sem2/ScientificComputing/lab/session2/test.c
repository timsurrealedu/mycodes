#include <stdio.h>

int lol(int A)
{
    A = A + 1;
    return A;
}

int main()
{
    printf("%d", lol(2));
}