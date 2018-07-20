#include <stdio.h>
#include <stdlib.h> 

enum{
	KEYWORD = 01,
	EXTERN  = 02,
	STATIC  = 04
};

struct sreg{
	unsigned keyword :1;
	unsigned neg	 :1;
	unsigned zero	 :1;
};

void showSreg(struct sreg *s){
	if(s != NULL){
		printf("keyword : %d\n",s->keyword);
		printf("neg     : %d\n",s->neg);
		printf("zero    : %d\n",s->zero);
	}
}

int main(){
	unsigned flag = 8;
	flag |= EXTERN |KEYWORD;			//turns on EXTERN and KEYWORD field
	char str[100];
	itoa(flag,str,2);
	printf("dec: %d\t bin:%s\n",flag,str);
	flag &= ~(EXTERN | KEYWORD);		//turns off EXTERN and KEYWORD field
	itoa(flag,str,2);
	printf("dec: %d\t bin:%s\n",flag,str);
	
	struct sreg *sr = NULL;
	sr = (struct sreg*) malloc(sizeof(struct sreg));
	sr->keyword = 2&0;
	sr->neg     = 1;
	sr->zero    = 0;
	showSreg(sr);
}
