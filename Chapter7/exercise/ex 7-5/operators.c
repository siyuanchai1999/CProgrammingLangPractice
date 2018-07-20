#include <stdio.h>

#include "operators.h"
#define OPARRSIZE 11
char operators[OPARRSIZE] = {
	'+',
	'-',
	'*',
	'/',
	'^',
	'%',
	'!',
	'c',
	's',
	'n',
	'p'
};

char getOp(int index){
	return operators[index];
}

int checkOPLib(char op){
	int i = 0;
	while(i < OPARRSIZE){
		if(op == operators[i]) return i;
		i++;
	}
	return -1;
}

double add(double a, double b){
	return a+b;
}

double substract(double Minuend, double Subtrahend){
	return Minuend - Subtrahend;
}

double multiply(double a, double b){
	return a*b;
}

double divide(double Dividend, double divisor){
	return Dividend/divisor;
}

double power(double base, double index){
	int i = (int) index;
	double result = 1;
	while(i > 0){
		result *= base;
		i--;
	}
	
	while(i < 0){
		result /= base;
		i++;
	}
	return result;
}

double module(double higher, double lower){
	int neg = 1;
	if(higher < 0){
		higher = higher *(neg = -1);
	}
	
	double result = higher - (int)(higher/lower) *lower;
	return result * neg;
}

double factorial(double fact){
	if(fact == (int) fact && fact > 0){
		if(fact > 1){
			return fact * factorial(fact -1);
		}else{
			return 1;
		}
	}else{
		printf("factorial only available for positive ints\n");
	}
}

double negate(double input){
	return input *(-1);
}

typedef double (*funcptr)(double,double);
funcptr funcArr[6] = {
	 add,	
	 substract,
	 multiply,
	 divide,
	 power,
	 module,
};

funcptr getFunc(int index){
	return funcArr[index];
}


