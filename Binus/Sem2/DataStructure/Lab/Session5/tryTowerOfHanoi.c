//example of recurstion
#include <stdio.h>

//define 
void towerOfHanoi(int n, char from, char to, char temp){
  if(n==0) return ;
  //1. pindahkan n-1 balok dari from ke temp
  towerOfHanoi(n-1,from,temp,to);
  //2. Pindahkan balok ke-n dari from ke to
  printf("%d %c %c\n",n,from,to);
  //3. Pindahkan n-1 balok dari temp ke to
  towerOfHanoi(n-1,temp,to,from);
}

int main(){
  int N;
  scanf("%d", &N);
  towerOfHanoi(N,'A','C','B');

}
