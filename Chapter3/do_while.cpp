#include <stdio.h>
/*convert n to characters in s*/
void itoa(int n, char s[]){
	int sign, i, save;
	if((sign = n)<0){
		if(n == -2147483648){
			n = -(n+1);
			save = 1;
		}else{
			n = -n;
			save = 0;
		}
	}
	i = 0;
	do{
		s[i++] = (char) (n%10+'0');
		n = n/10;
	}while(n>0);
	
	if(sign<0) s[i++] = '-';
	s[i] = '\0';
	//printf("%s %d",s,i);
	int j,k;
	char temp;
	for(j=0,k=i-1;j<k;j++,k--){  //revserse
		temp = s[j];
		s[j] = s[k];
		s[k] = temp;
	}
	if(save){
		s[i-1] = s[i-1] + 1;	
	}
	 
}

char single_digit(int x){  //int to char
	if(x>9){
		return (x-10) + 'A';
	}else if(x>=0){
		return x + '0';
	}
}

void itob(int n, char s[], int b){
	int i = 0,j,k,sign;
	if((sign = n)<0){
		n = -n;
	}
	do{
		if(sign>0){
			s[i++] = (char) single_digit(n%b);
		}else{
			if(i==0) s[i++] = (char) single_digit(b - n%b);
			else s[i++] = (char) single_digit(b - n%b - 1);
		}
		n = n/b;
	}while(n>0);
	while(sign<0 && i<4){
		s[i++] = single_digit(b-1);
	}
	s[i] = '\0';
	char temp;
	for(j=0,k=i-1;j<k;j++,k--){  //revserse
		temp = s[j];
		s[j] = s[k];
		s[k] = temp;
	}
	
}

int main(){
	int a = -2147483647;
	char s[100];
	itoa(a,s);
	printf("%s\n",s);
	int b = -2147483648;
	itoa(b,s);
	printf("%s\n",s);
	int c = -5;
	itob(c,s,16);
	printf("%s\n",s);
	c = -348;
	itob(c,s,16);
	printf("%s\n",s);
}
