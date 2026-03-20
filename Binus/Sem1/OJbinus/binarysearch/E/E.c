#include <stdio.h>

int main(){
    int T;
    scanf("%d", &T);
    for(int i=0;i<T;i++){
        int M;
        scanf("%d", &M);
        int yes = 0;
        int count = 1;
        while(yes<M){
            yes+=(count*count);
            count++;
        }
        printf("Case #%d: %d\n", i+1, count-1);
    }
}
