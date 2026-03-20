#include <stdio.h>

typedef struct{
  char name[100];
  int score;
}student;

int main(){
  student guy[100];
  printf("test");
  scanf("%d", &guy[0].score);
  printf("%d",guy[0].score);

}
