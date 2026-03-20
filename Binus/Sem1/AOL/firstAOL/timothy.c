#include <stdio.h>
#include <string.h>
#include <ctype.h>


int main(){
    char A[102];
    char B[102];

    scanf("%[^\n]", A);getchar();
    scanf("%[^\n]", B);

    int lengthA = strlen(A);
    int lengthB = strlen(B);

    char prefix[102];
    int countforprefix = 0;
    for(int i=0;i<lengthA;i++){
        if(A[i]==B[i]){
            prefix[i]=A[i];
            countforprefix++;
        }else{
            break;
        }
    }prefix[countforprefix] = '\0';

    int countSuff = 0;
    char Suffix[102];
    for(int i = lengthA;i>-1;i--){
        if(A[i]!=B[i]){
            countSuff = i;
            break;
        }
    }
    int startSuff=0;
    for(int i = countSuff;i<lengthA;i++){
        Suffix[startSuff]=A[i];
        startSuff++;
    }Suffix[startSuff]= '\0';


    int lengthsuffix=strlen(Suffix);
    int lengthprefix=strlen(prefix);
    char combine[lengthsuffix+lengthprefix+1];
    int countnew = 0;

    for(int i = 0;i<strlen(prefix);i++){
        combine[i]=prefix[i];
        countnew++;
    }for(int i=0;i<strlen(Suffix);i++){
        combine[countnew]=Suffix[i];
        countnew++;
    }combine[countnew]='\0';

    for(int i=0;i<strlen(combine);i++){
        if(isupper(combine[i])){
            printf("%c",tolower(combine[i]));
        }else{
            printf("%c",toupper(combine[i]));
        }
    }printf("\n");

}