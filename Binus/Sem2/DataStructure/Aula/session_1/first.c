#include <stdio.h>
//array is a data structure to find an index (check if it exists or not)

int main(){
    int N, Q, i;
    int A[100];
    int exist[100] = {0};

    scanf("%d", &N);
    for(i=0;i<N;i++){
        scanf("%d", &A[i]);
        exist[A[i]] = 1;
    }

    scanf("%d", &Q);
    for(i = 0;i<Q;i++){
        int x;
        scanf("%d", &x);
        if(exist[x]==1) printf("yes\n");
        else printf("no\n");
    }
}
