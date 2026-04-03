#include <stdio.h>
#include <stdlib.h>

int main(){
    int N, Q;
    scanf("%d %d",&N, &Q);
    int O[N+1];
    for(int i=0;i<N;i++){
        scanf("%d",&O[i]);getchar();
 
    }

    for(int i=0;i<Q;i++){
        char choice;
        int num1, num2;
        int final;
        scanf("%c %d %d", &choice, &num1, &num2);getchar();
        if(choice=='S'){
            final = 0;
            for(int j=num1-1;j<=num2-1;j++){
                final+=O[j];
            }
            printf("%d\n",final);
        }else if(choice=='U'){
            O[num1-1]=num2;
        }

    }
}