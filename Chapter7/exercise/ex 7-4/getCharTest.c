#include <stdio.h>
#include "getCharTest.h"
#define BUFFERSIZE 1000
char buff[BUFFERSIZE];
int bufp = 0;
int getch(){
	if(bufp>0){
		return buff[--bufp];
	}else{
		return getchar();
	}
}

int ungetch(char c){
	if(bufp >= BUFFERSIZE){
		printf("ERROR: too many characters\n");
		return -1;
	}else{
		//printf("push %d %c ")
		buff[bufp++] = c;
		return c;
	}
}

