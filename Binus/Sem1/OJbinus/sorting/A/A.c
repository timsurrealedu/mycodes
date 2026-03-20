#include <stdio.h>
#include <string.h>

void SortAsc(char* row, int n){
    for(int i=0;i<n;i++){
        for(int j=0;j<n-1-i;j++){
            if(row[j]>row[j+1]){
                char temp;
                temp = row[j];
                row[j]=row[j+1];
                row[j+1]=temp;
            }
        }
    }
}

int main(){
    int R, C;
    scanf("%d %d", &R, &C); 
    char a[201][201];
    
    
    for(int i=0;i<R;i++){
        scanf("%s", a[i]); 
    }

    for(int i=0;i<R;i++){ 
        SortAsc(a[i], C); 
    }

    for(int i=0;i<R;i++){
        for(int j=0;j<R-1-i;j++){
            if(strcmp(a[j],a[j+1]) < 0){ 
                char temp[201];
                strcpy(temp, a[j]);
                strcpy(a[j],a[j+1]);
                strcpy(a[j+1],temp);
            }
        }
    }

    for(int i=0;i<R;i++){
        printf("%s\n", a[i]); 
    }
    
    return 0;
}