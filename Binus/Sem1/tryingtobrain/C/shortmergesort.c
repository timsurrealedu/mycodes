#include <stdio.h>

void merge(int a[], int l, int m, int r, int tmp[]){
  int i=l, j=m+1, k=0;
  while(i<=m && j<=r) tmp[k++] = (a[i]<=a[j])? a[i++] : a[j++];
  while(i<=m) tmp[k++] = a[i++];
  while(j<=r) tmp[k++] = a[j++];
  for(i=0;i<k;i++) a[l+i]=tmp[i];a
}
void mergeSort(int a[], int l, int r, int tmp[]){
  if(l>=r) return;
  int m=(l+r)/2;
  mergeSort(a,l,m,tmp);
  mergeSort(a,m+1,r,tmp);
  merge(a,l,m,r,tmp);
}

int main(){
    
}
