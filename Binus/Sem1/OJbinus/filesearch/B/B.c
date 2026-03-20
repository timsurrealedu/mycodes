#include <stdio.h>
#include <string.h>

typedef struct{
    char name[100];
    char code[200];
}data;

int main(){
    FILE *fp = fopen("testdata.in", "r");
    int T;
    fscanf(fp, "%d", &T);
    data guy[T];
    for(int i=0;i<T;i++){
        fscanf(fp," %[^#]#%[^\n]", guy[i].name, guy[i].code);
    }
    int L;
    fscanf(fp, "%d", &L);
    char tempo[102];
    for(int i=0;i<L;i++){
        fscanf(fp, " %[^\n]", tempo);
        for(int j=0;j<T;j++){
            if(strcmp(tempo,guy[j].name)==0){
                printf("%s\n", guy[j].code);
                break;
            }
        }
    }
}