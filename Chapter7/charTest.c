#include <stdio.h>
#include <stdlib.h>

int main(){
	char *str = (char *) malloc(20);
	scanf("%s",str);
	while(*str){
		putchar(*str++);
	}
}
