#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

#define MAXOP 100
#define ZERO '0'
#define MAXVAL 100

int stackPos = 0;
double stack[MAXVAL];

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

double factorial(int num){
	if(num >1){
		return num*factorial(num-1);
	}else{
		return 1;
	}
}
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

void getAll(){
	int i;
	for(i = stackPos-1;i>=0;i--){
		printf("%d: %lf\n",stackPos-i,stack[i]);
	}
}

void clearAll(){
	int i;
	for(i = stackPos-1;i>=0;i--){
		stack[i] = '\0';
	}
}

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


