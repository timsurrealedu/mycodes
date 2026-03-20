#include <stdio.h> 

int f(int num){
    if(num==1) return 1;
    else if(num%2==0)return f(num/2);
    else if(num%2!=0)return f(num-1)+f(num+1);
    

}

int main(){
    int T;
    scanf("%d", &T); getchar();
    for(int i=0;i<T;i++){
        int num;
        scanf("%d", &num);getchar();
        int final = f(num);
        printf("Case #%d: %d\n", i+1, final);
    }
}