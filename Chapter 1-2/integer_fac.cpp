#include <stdio.h>

#define MAX 1000
int factors[MAX];

void display();
void factorize(long num);
int main(){
	factorize((long)2012);
	display();
}

void display(){
	for(int i = 0; i<MAX && factors[i]!= 0; i++){
		printf("%d, ",factors[i]);
	}
}

void factorize(long num){
	int last_value = 2;
	long j,k;
	k = 0;
	j = last_value;
	while(j<=num){
		if(num % j == 0){
			factors[k] = j;
			//j = last_value;
			num = num/j;
			k++;
		}else{
			j++;
		}
	}
}
