#include <stdio.h>
#include <stdarg.h>
/*
int int2str(int i,char *s){
	if(i< 0){
		*s++ = '-';
		i = i*(-1);
	}
	while(i>0){
		
		i /= 10
	}
}*/
void myprintf(char *fmt,...){
	va_list ap;
	char *p,*sval;
	int ival;
	double dval;
	
	va_start(ap, fmt);
	for(p = fmt; *p ; p++){
		if(*p != '%'){
			putchar(*p);
		}else{
			switch(*++p){
				case 'd':
					ival = va_arg(ap,int);
					printf("%d",ival);
					break;
				case 'f':
					dval = va_arg(ap,double);
					printf("%f",dval);
					break;
				case 's':
					for(sval = va_arg(ap,char *); *sval; sval++){
						putchar(*sval);
					}
					break;
				default:
					putchar(*p);
					break;
			}
		}
	}
	va_end(ap);
}

void testArg(int first,...){
	va_list ap;
	va_start(ap,first);
	int amount = 0;
	while(amount< 3){
		printf("%d arg = %d\n",amount++,va_arg(ap,int));
	}
	va_end(ap);
}
int main(){
	testArg(1,2,3);
}
