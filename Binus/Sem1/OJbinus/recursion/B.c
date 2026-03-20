#include <stdio.h>
#include <string.h>

void reverse(char* S, int start, int end){
    if(start>=end) return;
    char temp;
    temp = S[start];
    S[start]=S[end];
    S[end]=temp;
    reverse(S,start+1,end-1);
}

int main(){
    int T;
    scanf("%d", &T);getchar();
    for(int i=0;i<T;i++){
        char S[1003];
        scanf("%[^\n]s", S);getchar();
        int start = 0;
        int end = strlen(S)-1;
        reverse(S,start,end);
        printf("Case #%d: %s\n", i+1, S);

    }
}