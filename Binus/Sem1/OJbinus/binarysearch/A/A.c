#include <stdio.h>
#include <string.h>


typedef struct{
        char name[257];
        int score;
}player;

player guy[16000];

int binarySearch (player* arr, int size, char* target){
    int left = 0;
    int right = size - 1;

    while (left<=right){
        int mid = left + (right - left) / 2;
        int res = strcmp(arr[mid].name, target);
        if(res==0){
            return mid;
        }
        if(res<0){
            left = mid +1;
            
        }else{
            right = mid-1;
        }
    }
    return -1;
}

int main(){
    int T;
    scanf("%d", &T);

    for(int i=0;i<T;i++){
        scanf("%s %d", guy[i].name, &guy[i].score);
    }
    int M;
    char P1[257], P2[257];
    int numP1, numP2;
    int locP1, locP2;
    int foundP1 = 3;
    int foundP2 = 3;
    scanf("%d", &M);
    for(int i=0;i<M;i++){
        scanf("%s %s", P1, P2);
        if(strcmp(P1,P2)==0){
            printf("not valid\n");
            continue;
        }
        
        //for P1
        locP1=binarySearch(guy, T, P1);
        locP2=binarySearch(guy,T,P2);
        if(locP1==-1||locP2==-1){
            printf("not found\n");
            continue;
        }
        // for(int j=0;j<T;j++){
        //     if(strcmp(P1,guy[j].name)==0){
        //         numP1 = guy[j].score;
        //         locP1=j;
        //         break;
        //     }
        //     if(j==T-1){
        //         foundP1=0;
        //     }
        // }
        // //for P2
        // for(int j=0;j<T;j++){
        //     if(strcmp(P2,guy[j].name)==0){
        //         numP2=guy[j].score;
        //         locP2=j;
        //         break;
        //     }
        //     if(j==T-1){
        //         foundP2=0;
        //     }
        // }
        // if(foundP1==0||foundP2==0){
        //     printf("not found\n");
        //     foundP1=3;
        //     foundP2=3;
        //     continue;
        // }
        numP1=guy[locP1].score;
        numP2=guy[locP2].score;
        int first = numP1-numP2;
        if(first<0) first*=-1;
        int second = locP1-locP2;
        if(second<0) second*=-1;
        printf("%d %d\n", first, second);
    }


}