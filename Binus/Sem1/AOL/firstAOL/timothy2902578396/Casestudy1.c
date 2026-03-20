//Timothy Sebastian Darmawan - 2902578396
//Case study 1

#include <stdio.h>
#include <ctype.h>
#include <string.h>

int main(){
    char A[102];
    scanf("%s", A);getchar();
    char B[102];
    scanf("%s", B);

    int prefixcount = 0;
    char prefix[102];
    if(strlen(A)<strlen(B)){
        for(int i=0;i<strlen(A);i++){
            if(A[i]!=B[i]){
                prefixcount = i;
                break;
            }
            if(i==strlen(A)-1&&A[i]==B[i]){
                prefixcount = strlen(A);
            }
        }
        for(int i=0;i<prefixcount;i++){
            prefix[i]=A[i];
        }
        prefix[prefixcount]= '\0';
    }
    if(strlen(A)>strlen(B)){
        for(int i=0;i<strlen(B);i++){
            if(A[i]!=B[i]){
                prefixcount = i;
                break;
            }
            if(i==strlen(B)-1&&A[i]==B[i]){
                prefixcount = strlen(B);
            }
        }
        for(int i=0;i<prefixcount;i++){
            prefix[i]=A[i];
        }
        prefix[prefixcount]= '\0';
    }
    if(strlen(A)==strlen(B)){
        for(int i=0;i<strlen(A);i++){
            if(A[i]!=B[i]){
                prefixcount = i;
                break;
            }
            if(i==strlen(A)-1&&A[i]==B[i]){
                prefixcount = strlen(A);
            }
        }
        for(int i=0;i<prefixcount;i++){
            prefix[i]=A[i];
        }
        prefix[prefixcount]= '\0';

    }
    

    char suffix[102];
    int suffixcount=0;
    if(strlen(A)>strlen(B)){
        int lengthB = strlen(B);
        suffixcount = strlen(A)- strlen(B);
        for(int i=strlen(A)-1;i>=0;i--){
            lengthB--;
            if(lengthB<0) continue;
            if(A[i]!=B[lengthB]){
                suffixcount = i+1;
                break;
            }
            
        }
        int counter = 0;
        for(int i=suffixcount;i<strlen(A);i++){
            suffix[counter]=A[i];
            counter++;
        }
        suffix[counter]='\0';
    }
    else if(strlen(A)<strlen(B)){
        int lengthA = strlen(A);
        suffixcount = strlen(B)-strlen(A);
        for(int i=strlen(B)-1;i>=0;i--){
            lengthA--;
            if(lengthA<0) continue;
            if(B[i]!=A[lengthA]){
                suffixcount = i+1;
                break;
            }
            
        }
        int counter = 0;
        for(int i=suffixcount;i<strlen(B);i++){
            suffix[counter]=B[i];
            counter++;
        }
        suffix[counter]='\0';

    }
    else if(strlen(A)==strlen(B)){
        for(int i=strlen(A);i>=0;i--){
            if(A[i]!=B[i]){
                suffixcount = i+1;
                break;
            }
        }
        int counter = 0;
        for(int i=suffixcount;i<strlen(A);i++){
            suffix[counter]=A[i];
            counter++;
        }
        suffix[counter]='\0';

    }

    

    if(prefixcount == 0 && suffixcount == strlen(A)){
        printf("No Output\n");
        return 0;
    }
    else if(prefixcount == 0 && suffixcount != strlen(A)){
        char final[204];
        int tempfinal = 0;
        for(int i=0;i<strlen(suffix);i++){
            if(isupper(suffix[i])){
                final[i]=tolower(suffix[i]);
                tempfinal = i;
            }else{
                final[i]=toupper(suffix[i]);
                tempfinal = i;
            }
        }final[tempfinal+1] = '\0';
        printf("%s\n", final);
        return 0;
    }
    else if(suffixcount == strlen(A) && prefixcount != 0){
        char final[204];
        int tempfinal = 0;
        for(int i=0;i<strlen(prefix);i++){
            if(isupper(prefix[i])){
                final[i]=tolower(prefix[i]);
                tempfinal = i;
            }else{
                final[i]=toupper(prefix[i]);
                tempfinal = i;
            }
        }final[tempfinal+1]='\0';
        printf("%s\n", final);
        return 0;
    }
    else{
        char combined[204];
        int tempfinal = 0;
        int tempcount = 0;
        for(int i=0;i<strlen(prefix);i++){
            combined[i]=prefix[i];
            tempcount = i;
        }for(int i=0;i<strlen(suffix);i++){
            combined[tempcount+1] = suffix[i];
            tempcount++;
        }
        combined[tempcount+1] = '\0';
        char final[204];
        for(int i=0;i<strlen(combined);i++){
            if(isupper(combined[i])){
                final[i] = tolower(combined[i]);
                tempfinal = i;
            }else{
                final[i] = toupper(combined[i]);
                tempfinal = i;
            }
        }final[tempfinal+1]='\0';
        printf("%s\n", final);
        return 0;
    }

}