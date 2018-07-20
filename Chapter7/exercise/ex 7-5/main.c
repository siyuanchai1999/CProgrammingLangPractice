#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <float.h>

#include "getCharTest.h"
#include "stack.h"
#include "operators.h"
#define KEYLEN 100
/* run this program using the console pauser or add your own getch, system("pause") or input loop */
/**
every keyword comes in one line
keyword is defined as number(int/double) and operator
*/
//problem how to handle negatic values??
int getkey(char *w, int lim){
	int c;
	while(isspace(c = getch()))
		;
	int index = -1, afterdot = 0;
	if((index = checkOPLib(c)) != -1){
		*w++ = getOp(index);
		*w = '\0';
		if(!(c == '-' && isdigit(c = getch()))){
			//ungetch(c);
			return index;	
		} 
	}
	
	if(isdigit(c)){
		*w++ = c;
		while(isdigit(c = getch()) || (c == '.' && !afterdot) ) {
			if(c == '.') afterdot = 1;
			*w++ = c;
		}
		if(!isspace(c)) ungetch(c);
		*w = '\0';
		return OPARRSIZE;
	}
	*w++ = c;
	*w = '\0';
	return -1; //abnormal char
}

void binOp(int index){
	double current = pop();
	double previous = pop();
	printf("%g %c %g=%g\n",previous,getOp(index),current,push(getFunc(index)(previous,current)));
}



void caculator(){
	int keyresult;
	double dval = DBL_MAX, previous, current;
	char op;
	char key[KEYLEN];
	while(stackinSize()){
		//printf("in size loop\n");
		if( (keyresult = getkey(key,KEYLEN)) < OPARRSIZE && keyresult != -1){
//			printf("key = %s\n",key);
			if( key[0] == 's'){
				showStack();
			}else if(key[0] == 'c'){
				clearStack();
			}else if(key[0] == '!' && getStackNum() >0){
				printf("%g\n",push(factorial(pop())) );
			}else if(key[0] == 'n' && getStackNum() > 0){
				printf("%g\n",push(negate(pop())));
			}else if(key[0] == 'p' && getStackNum() >0){
				printf("pop out %g\n",pop());
			}else if(getStackNum() > 1){
				binOp(keyresult);
			}else{
				printf("stack not sufficient for operation: %c\n",key[0]);
			}		
		}else if(keyresult == OPARRSIZE){
			sscanf(key,"%lf",&dval);
			push(dval);
			printf("dval = %lf was pushed onto stack\n",dval);
		}else{
			printf("invalid input %c\n",key[0]);
		}
	}
}
int main(){
	caculator();
	
}

