#include <stdio.h>
#include <stdlib.h>
#define MAXVAL 100
#include "calc.h"

int stackPos = 0;
double stack[MAXVAL];

void push(double f){
	if(stackPos<MAXVAL){
		stack[stackPos++] = f;
	}else{
		printf("Full stack!");
	}
}

double pop(void){
	if(stackPos>0){
		return stack[--stackPos];	
	}else{
		printf("Empty stack!!");
		return 0.0;
	}
}

double factorial(int num){
	if(num >1){
		return num*factorial(num-1);
	}else{
		return 1;
	}
}

double getTop(void){
	double temp;
	if(stackPos>=1){
		temp =  stack[stackPos-1];
		return temp;
	}else{
		printf("Empty stack in getTop!!");
		return 0.0;
	}
}

void swap(void){
	double temp;
	temp = stack[--stackPos];
	stack[stackPos] = stack[stackPos-1];
	stack[stackPos -1] = temp;
	stackPos++;
}

void getAll(void){
	int i;
	for(i = stackPos-1;i>=0;i--){
		printf("%d: %lf\n",stackPos-i,stack[i]);
	}
}

void clearAll(void){
	int i;
	for(i = stackPos-1;i>=0;i--){
		stack[i] = '\0';
	}
}
