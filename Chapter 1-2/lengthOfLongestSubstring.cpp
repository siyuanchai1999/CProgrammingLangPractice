#include <stdio.h>
int lengthOfLongestSubstring(char s[]);
int inLastentry(char t[], char m);
int main(){
	char p[] = "pwwkew";
	printf("%d",lengthOfLongestSubstring(p));
}




int lengthOfLongestSubstring(char s[]) {
    int length = 0;
    int i,j = 0;
    char temp[50];
    for(i = 0; s[i]!='\0';i++){
        if(!inLastentry(temp,s[i])){
            temp[j++] = s[i];
        }else{
            if(j>length) length = j;
            j = 0;
            for(int c=0; temp[c]!= '\0'; c++){  //clear temp
                temp[c] = '\0';
            }
            temp[j++] = s[i];
        }
    }
    return length;
}

int inLastentry(char t[], char m){
    for(int k = 0; t[k]!= '\0'; k++){
        if(t[k] == m){
            return 1;
        }
    }
    return 0;
}
