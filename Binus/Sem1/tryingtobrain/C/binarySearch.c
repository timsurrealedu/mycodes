#include <stdio.h>

// int binarySearch(int* nums, int find, int l, int r){
//     int mid = l + (r-l)/2;
//     if(nums[mid] == find) return mid;
//     else if(nums[mid]>find) return binarySearch(nums, find, l, mid-1);
//     else return binarySearch(nums, find, mid+1, r);
// }

int search(int* nums, int l, int r, int target){
    int mid = l+(r-l)/2;
    if(nums[mid] == target) return mid;
    else if(nums[mid]<target) return search(nums, mid+1, r, target);
    else return search(nums, l, mid-1, target);
}

int main(){
    int nums[] = {0,1,2,3,4,5,6,7,8,9};
    int index = search(nums,4,0,9);
    printf("%d", index);
}