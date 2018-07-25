#include <stdio.h>
#include <ctype.h>

#define SIZE 5
void swap(int *px, int *py);
void outputArr(double *arr);
int main(){
	int c = 5, x = 1, y = 2;
	swap(&x, &y);
	printf("x:%d\n",x);
	printf("y:%d\n",y);
	printf("%d\n",isdigit(EOF));
	//EOF == -1 (numerically)
	//to cause EOF, tyep control^Z
	//running getint
	
	
	int n;
	double array[SIZE];
	outputArr(array);
	for(n = 0;n<SIZE && getDouble(&array[n]) != EOF; n++)
		;
	outputArr(array);
}

void swap(int *px, int *py){
	int temp;
	temp = *px;
	*px = *py;
	*py = temp;
}

int getDouble(double *pn){
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
	
	int divNum = -1;
	for(*pn = 0; isdigit(c) || c=='.'; c = getchar()){
		if(divNum>=0) divNum++;
		if(isdigit(c))  *pn = 10 * (*pn) + (c - '0');
		if(c == '.') divNum++;
	}
	while(divNum>0){
		*pn = *pn/10;
		divNum--;
	}
	*pn = *pn * sign;
	return c;
}

void outputArr(double *arr){
	int i;
	for(i=0;i<SIZE;i++){
		printf("spot %d : %f\n",i,*(arr+i));
	}
	printf("array output finished...\n");
}
