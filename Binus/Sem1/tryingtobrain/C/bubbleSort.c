// #include <stdio.h>
// 
// int main(){
    // int a[] = {1,3,7,9,0,2,4,5,8,6};
    // int length = sizeof(a)/sizeof(a[0]);
    // printf("%d", length);
// 
    // for (int i=0; i<length;i++){
        // for(int j=0;j<length-1;j++){
            // if(a[j]>a[j+1]){
                // int temp = a[j];
                // a[j]=a[j+1];
                // a[j+1]=temp;
            // }
        // }
    // }
// 
    // for(int i =0;i<length;i++){
        // printf("a[%d]=%d\n", i, a[i]);
    // }
// }
// 

#include <stdio.h>

void sortAscending(int* nums, int length){
    for(int i=0;i<length;i++){
        for(int j=0;j<(length-1);j++){
            if(nums[j]>nums[j+1]){
                int temp = nums[j];
                nums[j]=nums[j+1];
                nums[j+1]=temp;
            }
        }
    }
}

void sortDescending(int* nums, int length){
    for(int i=0;i<length;i++){
        for(int j=0;j<length-1;j++){
            if(nums[j]<nums[j+1]){
                int temp;
                temp = nums[j];
                nums[j]=nums[j+1];
                nums[j+1]=temp;
            }
        }
    }
}

int main(){
    int nums[] = {5, 3, 1, 2, 6, 9, 4, 8, 7};
    int length = sizeof(nums)/sizeof(nums[0]);
    sortAscending(nums, length);
    for(int i =0;i<length;i++){
        printf("%d", nums[i]);
    }
}

