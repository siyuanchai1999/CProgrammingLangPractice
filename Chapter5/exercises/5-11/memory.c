#include <stdio.h>
#include "memory.h"

#define ALLOCSIZE 10000

static char allocbuf[ALLOCSIZE];
static char *allocp = allocbuf;

void printTest(){
	printf("header works!!\n");
}

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
