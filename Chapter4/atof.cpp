#include <stdio.h>
#include <ctype.h>

#define MAX 100

int getline(char s[], int lim){
	int c,i;
	i = 0;
	while(--lim>0 && (c=getchar())!= EOF && c !='\n'){
		s[i++] = c;
	}
	if(c == '\n') s[i++] = c;
	s[i] = '\0';
	return i;
}

/*convert string s to double*/
double atof(char s[]){
	double val, power,exp,times;
	int i,k,sign,ex_sign;
	times = 1.0;
	sign = 1;
	ex_sign = 1;
	
	for(i = 0;isspace(s[i]);i++)
		;
	if(s[i] == '+'){
		i++;
	}else if(s[i] == '-'){
		sign = -1;
		i++;
	}
	
	for(val = 0.0; isdigit(s[i]);i++){
		val = 10*val + s[i] - '0';
	}
	if(s[i] == '.') i++;
	for(power = 1.0;isdigit(s[i]);i++){
		val = 10*val + s[i] - '0';
		power = power *10.0;
	}
	if(s[i] == 'e' || s[i] == 'E'){
		i++;
		if(s[i] == '+') i++;
		else if(s[i] == '-')
			i++;
			ex_sign = -1;
	}
	for(exp = 0.0;isdigit(s[i]);i++){
		exp = exp*10.0 + s[i] - '0';
	}
	for(k = 0;k<exp; k++){
		if(ex_sign>0) times = times * 10.0;
		if(ex_sign<0) times = times / 10.0;
	}
	return (sign*val/power)*times;
}

int main(){
	
	char line[MAX];
	double sum = 0;
	int m = 1;
	while(m>0){
		m = getline(line, MAX);
		printf("m: %d", m);
		//printf("%g\n",sum+=atof(line));
	}
}
