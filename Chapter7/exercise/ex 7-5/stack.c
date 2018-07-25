#include <stdio.h>
#include "stack.h"

#define STACKSIZE 1000

double stack[STACKSIZE];
double *stackptr = stack;

double push(double entry){
	if(stackptr - stack <STACKSIZE){
		*stackptr++ = entry;
		return entry;
	}else{
		printf("stack overflow\n");
		return -1;
	}
}

double pop(){
	if(stackptr > stack && stackptr< stack + STACKSIZE){
		return *(--stackptr);
	}else{
		printf("no element in stack\n");
	}
}

int stackinSize(){
	return stackptr >= stack && stackptr< stack + STACKSIZE;
}

int getStackNum(){
	return stackptr - stack;
}

void clearStack(){
	stackptr = stack;
}

void showStack(){
	double *temp = stackptr;
	printf("stack start------------\n");
	while(temp-- > stack){
		printf("%lf\n",*temp);
	}
	printf("stack end--------------\n");
}
