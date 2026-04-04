#include <stdio.h>
#include <stdlib.h>


void testa(int num){
    num=2;
}

int main(){
   int num = 3;
   testa(num);
   printf("%d\n",num);
}