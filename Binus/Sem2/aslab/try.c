#include <stdio.h>
#include <stdlib.h>

/*int main(){
  char this;
  this = getchar();
  putchar(this);
  char that[30];
  gets(that);
  puts(that);
}*/

int main(){
  int a = 10;
  int *p = &a;

  *p = 15;

  printf("nilai variable a: %d\n", a);
  printf("alamat variable a: %d\n", &a);
  printf("akses nilai variabe a menggunakan pointer p: %d\n", *p);
  printf("akses nilai alamat a menggunakan pointer p: %d\n", p);
  printf("alamt pointer p: %d\n", &p);

  return 0;

 }
