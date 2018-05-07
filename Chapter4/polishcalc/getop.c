#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include "calc.h"
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

int getop(char s[]){
	int i = 0,m = 0;
	if(m = getline(s,100)){
		if(!isdigit(s[0]) && s[0] != '.'&& s[0]!='\0'){
			return s[0];
		}else{
			return ZERO;
		}	
	}else{
		return EOF;
	}
}
