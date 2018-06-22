#include <stdio.h>
#include <string.h>
#define ALLOCSIZE 1000

void strcpy(char *a, char *b){
	
	while(*a != '\0'&& *b != '\0'){
		printf("a address: %d, value: %c\t",a,*a);
		printf("b address: %d, value: %c\n",b,*b);
		*a = *b;
		a++; b++;
		printf("a address: %d, value: %c\t",a,*a);
		printf("b address: %d, value: %c\n",b,*b);
	}
}

static char allocbuf[ALLOCSIZE];
static char *allocp = allocbuf;
char *alloc(int n){
	if(allocbuf + ALLOCSIZE - allocp >=n ){
		allocp += n;
		return allocp - n;
	}else{
		return 0;
	}
}

void afree(char *p){
	if(p>=allocbuf && p<allocbuf+ALLOCSIZE){
		allocp = p;
	}
}


int main(){
	char *lineptr[100];
	lineptr[1] = alloc(5);
	
	printf("a address: %d, value: %d\t",lineptr[1],*lineptr[1]);
	return 0;
}


