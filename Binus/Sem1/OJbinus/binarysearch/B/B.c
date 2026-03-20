#include <stdio.h>
#include <string.h>

int binarySearch(int* arr, int size, int target){
    int left = 0;
    int right = size-1;
    int foundIndex = -2;
    while(left<=right){
        int mid = left +(right-left) / 2;
        if(arr[mid]==target){
            foundIndex = mid;
            right = mid-1;
        }
        if(arr[mid]<target){
            left = mid+1;
        }else{
            right = mid -1;
        }
    }
    return foundIndex;
}

int main(){
    int N, M;
    scanf("%d %d", &N,&M);
    int A[N+2];
    int Q[M+2];
    for(int i=0;i<N;i++){
        scanf("%d", &A[i]);
    }
    for(int i=0;i<M;i++){
        scanf("%d", &Q[i]);
    }
    for(int i=0;i<M;i++){
        int result = binarySearch(A, N, Q[i]);
        printf("%d\n",result+1);
    }

}