#include <stdio.h>
#include <limits.h>
#include <string.h>

int hexStr_to_int(char s[]);
int power(int base, int exp);
int main(){
	//initialization value must be a constant
	printf("%d\n", power(16,3));
	char str[] = "3af";
	printf("%d\n",hexStr_to_int(str));
	//printf("%d\n",strlen(str));
	
	
}

int power(int base, int exp){
	int result = 1;
	for(int j=0; j<exp; j++){
		result = result * base;
	}
	return result;
}

int hexStr_to_int(char s[]){
	int length = strlen(s);
	int result = 0;
	for(int i=0;s[i] != '\0'; i++){
		if(s[i] >= '0' && s[i]<= '9'){
			result += (s[i] -'0') * power(16, length -i -1);
		}else if((s[i] >= 'a' && s[i]<= 'f')){
			result += (s[i] -'a'+10) * power(16, length-i-1);
		}else if((s[i] >= 'A' && s[i]<= 'F')){
			result += (s[i] -'A'+10) * power(16, length -i-1);
		}
	}
	return result;
}
