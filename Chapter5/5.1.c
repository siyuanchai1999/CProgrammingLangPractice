#include <stdio.h>
#include <ctype.h>

#define SIZE 5
void swap(int *px, int *py);
void outputArr(int *arr);
int main(){
	int c = 5, x = 1, y = 2;
	swap(&x, &y);
	printf("x:%d\n",x);
	printf("y:%d\n",y);
	printf("%d\n",isdigit(EOF));
	//EOF == -1 (numerically)
	//to cause EOF, tyep control^Z
	//running getint
	
	
	int n, array[SIZE];
	outputArr(array);
	for(n = 0;n<SIZE && getint(&array[n]) != EOF; n++)
		;
	outputArr(array);
}

void swap(int *px, int *py){
	int temp;
	temp = *px;
	*px = *py;
	*py = temp;
}

int getint(int *pn){
	int c, sign = 1;
	int going = 0;
	while(isspace(c = getchar())){
		;
	}
	while(!going){  //change made for ex5-1,  a bool going to prevent invalid from taking the place
		going = 1;
		if(!isdigit(c) && c != EOF && c != '+' && c != '-'){
			going = 0;
			c = getchar(); //not a number
		}
		if(c == '+'){
			sign = 1;
			c = getchar();
			if(c == 10){ c = '+'; going = 0;	} 
		}else if (c == '-'){
			sign = -1;
			c = getchar();
			if(c == 10){ c = '-'; going = 0;}
		}
	}
	
	int be;
	for(*pn = 0; isdigit(c) || c=='.'; c = getchar()){
		*pn = 10 * (*pn) + (c - '0');
	}
	*pn = *pn * sign;
	if(c != EOF){
		ungetch(c);
	}
	return c;
}

void outputArr(int *arr){
	int i;
	for(i=0;i<SIZE;i++){
		printf("spot %d : %d\n",i,*(arr+i));
	}
	printf("array output finished...\n");
}
