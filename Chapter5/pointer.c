#include <stdio.h>
#include <ctype.h>
/*
int *iq = &x; //assign address of x to iq pointer
*iq //access the value in address iq
++*iq  (*iq)++ //increase the value in address iq by one
*iq++ //increase the memory address at iq

*/

void swap(int *px, int*py){
	int temp = *px;
	*px = *py;
	*py = temp;	
}

int getint(int *pn){
	int c, sign;
	sign = 1;
	while(isspace(c = getch()))	
		;
	if(!isdigit(c) && c!=EOF && c!='+' && c!= '-'){
		ungetch(c);
		return 0;
	}
	if(c == '+'){
		c = getch();
	}else if (c == '-'){
		sign = -1;
		c = getch();
	}
	for(*pn = 0;isdigit(c);c=getch()){
		printf("%c",c);
		*pn = (*pn) *10 + (c-'0');
	}
	*pn = (*pn)*sign;
	return c;
}
int main(){
	int a = 10;
	int b = 9;
	printf("a:%d  b:%d\n",a,b);
	swap(&a,&b);
	printf("a:%d  b:%d\n",a,b);
	while(getint(&a)!=0){
		printf("a:%d  b:%d\n",a,b);
	}	
}
