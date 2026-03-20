#include <stdio.h>

void towerOfHanoi(int n, char asal, char tujuan, char pembantu){
  if(n==1){
    printf("Pindahkan piringan 1 dari tiang %c ke tiang %c\n", asal, tujuan);
    return;
  }
  towerOfHanoi(n-1, asal, pembantu, tujuan);
  printf("Pindahkan piringan %d dari tiang %c ke tiang %c\n", n, asal, tujuan );
  towerOfHanoi(n-1,pembantu,tujuan, asal); 
}

int main(){
  int n;
  printf("Masukkan jumlah piringan: ");
  scanf("%d", &n);
  printf("Langkah-langkah pemindahan: \n");
  towerOfHanoi(n,'A','C','B' );
}
