#include <stdio.h>
#define BUFFERSIZE 1000
char buffer[BUFFERSIZE];
int bufp = 0;
int getch(){
	if(bufp>0){
		return buffer[--bufp];
	}else{
		return getchar();
	}
}

int ungetch(char c){
	if(bufp >= BUFFERSIZE){
		printf("ERROR: too many characters\n");
		return -1;
	}else{
		buffer[bufp++] = c;
		return c;
	}
}

