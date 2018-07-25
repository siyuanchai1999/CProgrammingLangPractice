#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include "calc.h" 

#define MAXOP 100
#define ZERO '0'

int main(){
	int type;
	double op1;
	double op2;
	char s[MAXOP];
	
	while((type = getop(s)) != EOF){
		switch(type){
			case ZERO:
				printf("input:%s",s);
				push(atof(s));
				break;
			case '+':
				printf("plus");
				push(pop() + pop());
				printf("  result:%lf\n",getTop());
				break;
			case '-':
				printf("minus");
				op2 = pop();
				push(pop() - op2);
				printf("  result:%lf\n",getTop());
				break;
			case '*':
				printf("multiply");
				push(pop() * pop());
				printf("  result:%lf\n",getTop());
				break;
			case '/':
				printf("division");
				if((op2 = pop()) != 0){
					push(pop()/op2);
					printf("  result:%lf\n",getTop());
				}else{
					printf("Error: zero divisor");
				}
				break;
			case '%':
				printf("modulus");
				op2 = pop();
				op1 = pop();
				if(op1>0 && op2 >0){
					push(op1 - ((int) (op1/op2)) * op2);
					printf("  result:%lf\n",getTop());
				}else{
					printf("Eorro: negative module");
				}
				break;
			case '!':
				push(factorial((int) pop()));
				printf("  result:%lf\n",getTop());
				break;
			case '|':
				printf("  result:%lf\n",getTop());
				break;
			case 's':
				swap();
				printf("swap top two");
				break;
			case 'a':
				getAll();
				break;
			case 'c':
				clearAll();
				break;
			default:
				printf("error: unknown commands: %s",s);
				break;
		}
	}
	return 0;
}


