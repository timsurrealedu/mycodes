#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(){
    int a,b;
    scanf("%d %d",&a, &b);getchar();
    int numbs[a+1];
    for(int i = 0 ; i < a; i++){
       scanf("%d",&numbs[i]);getchar();
    }
    for(int i = 0 ; i < a ; i++){
        printf("%d ",numbs[i]);
    }
}
