#include <stdio.h>
#include <stdlib.h>

#define ARRSIZE 10
int main(){
	int *p = (int *) malloc(ARRSIZE);			//malloc allocate n bytes without initialization
	int *q = (int *) calloc(ARRSIZE,sizeof(int)); //calloc allocates initialized arr
	int i;
	for(i = 0;i<ARRSIZE;i++){
		printf("%d\t",*p);
	}
	printf("\n");
	for(i = 0;i<ARRSIZE;i++){
		printf("%d\t",*q);
	}
}
