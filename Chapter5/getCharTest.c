#include <stdio.h>

int main(){
	char c;
	
	int i = 0;
	while((c = getchar()) != EOF){
		printf("Input %d: %d\n",i++,c);
		c = getchar();
	}
}
