#include <stdio.h>

long long count=0;

long long func(int N){
    
    if(N%3==0){
        count++;
    }
    else if(N==0) return 1;
    else if(N==1) return 2;
    else if(N%5==0) return N*2;
    else return func(N-1) + N + func(N-2) + N -2;
}

int main(){
    int T;
    scanf("%d", &T);
    for(int i=0;i<T;i++){
        int N;
        scanf("%d", &N);
        count = 0;
        long long int ans = func(N);
        printf("%d %d\n", ans, count);
    }
}

