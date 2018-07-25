#include <stdio.h>
#include "memory.h"

#define MAXNUM 100
#define MAXOP  100
#define ALLOCSIZE 10000 


int stackNum[MAXNUM];
int stackNumInc = 0, operatorsInc = 0;
char *operators;

static char allocbuf[ALLOCSIZE];
static char *allocp = allocbuf;

void printTest(){
	printf("header works!!\n");
}

char *alloc(int n){
	if(allocbuf + ALLOCSIZE - allocp >=n ){
		allocp += n;
		return allocp - n;
	}else{
		return 0;
	}
}
		
void afree(char *p){
	if(p>=allocbuf && p<allocbuf+ALLOCSIZE){	
		allocp = p;
	}
}

int charToInt(char *str){
	int c,result = 0;
	while(c = *str++ ){
		if(isdigit(c)){
			result = result*10 + (c-'0');	
		}else{
			return -1;
		}
	}
	return result;
}	

void outputStackNum(){
	printf("stackNum:\t");
	int i;
	for(i = 0; i<stackNumInc;i++){
		printf("%d\t",*(stackNum+i));
	}
	printf("stackNumInc: %d\n", stackNumInc);
}

void outputOperators(){
	printf("operators:\t");
	int i;
	for(i = 0; i<operatorsInc;i++){
		printf("%c\t",*(operators+i));
	}
	printf("\n");
}

int stackNumPop(){
	if(stackNumInc>0){
		int result =  *(stackNum + stackNumInc - 1);
		*(stackNum + (--stackNumInc)) = '\0';
		return result;
	}
	return 0;
}

void stackNumPush(int num){
	*(stackNum + stackNumInc++) = num;
}


int main(int argc, char *argv[]){
	operators = alloc(MAXOP);
	int result,c;
	
	//read in
	while(--argc>0){
		c = **(++argv);
		if((isdigit(c) || c=='-') && (stackNumInc<MAXNUM)) {
			*(stackNum + stackNumInc++) = charToInt(*argv);
		}else if((c == '+'|| c == '-' || c == '*' || c == '/') && (operatorsInc<MAXOP)){
			*(operators + operatorsInc++)= c;
		}else{
			printf("illegal parameters %c, or input oversize\n",c);
			argc = -1;
		}
	}
//	outputStackNum();
//	outputOperators();
	while(operatorsInc-->0 && argc != -1){
		c = *(operators++);
		if(c == '+'){
			result = stackNumPop() + stackNumPop();
		}else if(c == '-'){
			result = stackNumPop() - stackNumPop();
		}else if(c == '*'){
			result = stackNumPop() * stackNumPop();
		}else if (c == '/'){
			result = stackNumPop() / stackNumPop();
		}
		stackNumPush(result);
	}
	printf("result:%d",stackNumPop());
	
}
