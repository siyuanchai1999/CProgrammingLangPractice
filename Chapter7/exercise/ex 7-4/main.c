#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

#include "getCharTest.h"
#define BUFFERS 100
/* run this program using the console pauser or add your own getch, system("pause") or input loop */

char buffer[BUFFERS];
char *bufptr = buffer;

void waitNextLine(){
	int c;
	while((c= getch() )!= '\n' && c != EOF)
		;
}


int checkfmt(char *start, char *end){
	printf("show buffer:");
	char *temp = start;
	for(;temp<end;temp++){
		printf("%c",*temp);
	}
	putchar('\n');
	for(;start<end;start++){
		if(*start != getch()){
			waitNextLine();
			return 0;
		}
	}
	return 1;
}

double tenmi(int index){
	return (index == 0)? 1 : 10 *tenmi(--index);
}



double stream2double(int *cont){
	int c, neg = 1,afterdot = 0;
	double result = 0;
	while(isspace(c = getch()))
		;
	
	while(*cont && !isdigit(c)){
		if(!afterdot && c == '-'){
			neg = -1;
		}else if(c == '.'){
			afterdot = 1;
		}else{
			*cont = 0;
		}
		c = getch();
	}
	
	while(isdigit(c) || (c == '.' && !afterdot) ){
		if(isdigit(c)){
			result = afterdot ? (result + (c - '0')/tenmi(afterdot++)) : (result*10 + c - '0');
		}else if(c == '.'){
			afterdot = 1;
		}
		c = getch();
	}
	if(!isspace(c)) ungetch(c);
	return result * neg;
}

int stream2int(int *cont){
	int c, result = 0, neg = 1;
	while(isspace(c = getch()))
		;
		
	if(c == '-'){
		neg = -1;
		if(isdigit(c = getch())){
			result = result *10 + c - '0';
		}else{
			*cont = 0;
		}
	}else if(isdigit(c)){
		result = c - '0';
	}else{
		*cont = 0;
		return 0;
	}
	
	while(isdigit(c = getch())){
		result = result*10 + c - '0';
	}
	if(!isspace(c)) ungetch(c);
	return result * neg;
}


char *findkey(char *p){
	while(isdigit(*p) || *p == '-' || *p == '.'|| isspace(*p))
		p++;
	return p;
}

void myscanf(char *fmt,...){
	va_list ap;
	char *p, *temp, *charptr;
	va_start(ap,fmt);
	int cont = 1, bufferlen = 0,ival,c;
	int *err,*intptr;
	double dval,*dptr;
	
	for(p = fmt; *p && cont; p++){
		if(isspace(*p)){
			//skip
		}else if(*p == '%'){
			temp = ++p;
			p = findkey(p);
			if(cont = checkfmt(buffer,bufptr)){
				switch(*p){
					case 'd':
						ival = stream2int(&cont);
						if(cont){
							intptr = va_arg(ap,int *);
							*intptr = ival;
						}
						break;
					case 's':
						charptr = va_arg(ap,char *);
						while((c = getch()) != EOF && c != '\n'){
							*charptr++ = c;
						}
						break;
					case 'f':
						dval = stream2double(&cont);	
						if(cont){
							dptr = va_arg(ap,double *);
							*dptr = dval;
						}
						break;
					}
			}
			//printf("assign buffer %d to bufptr %d\n",buffer, bufptr);
			bufptr = buffer;
		}else{
			*bufptr++ = *p;
		}
	}
}
int main() {
	char s[18] = "while";
	double a = 3.14;
	int b = 9;
	myscanf("str%sfloat%fint%d",s,&a,&b);
	printf("s = %s \ta = %f \t b = %d",s,a,b);
	/*
	while(1){
		myscanf("beijing%d tianjin%d",&a,&b);
		printf("a = %d \t b = %d\n",a,b);		
	}
	*/

}
