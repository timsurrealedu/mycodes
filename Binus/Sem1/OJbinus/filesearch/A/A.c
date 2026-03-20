#include <stdio.h>

typedef struct{
    int NIM;
    char name[22];
}student;

int main(){
    FILE *fp = fopen("testdata.in", "r");
    int T;
    fscanf(fp, "%d", &T);
    student guy[T];
    for(int i=0;i<T;i++){
        fscanf(fp,"%d ",&guy[i].NIM);
        fscanf(fp,"%s", guy[i].name);
        printf("%d %s\n",guy[i].NIM, guy[i].name);
    }
    int L;
    fscanf(fp,"%d", &L);
    int temp;
    for(int i=0;i<L;i++){
        fscanf(fp,"%d", &temp);
        for(int j=0;j<T;j++){
            if(temp==guy[j].NIM){
                printf("Case #%d: %s\n", i+1, guy[j].name);
                break;
            }else if(temp!=guy[j].NIM && j == T-1){
                printf("Case #%d: N/A\n", i+1);
            }
        }
    }
    fclose(fp);
}