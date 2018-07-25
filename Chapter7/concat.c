#include <stdio.h>

void fileappend(FILE *dest, FILE *src){
	int c;
	while((c = getc(src)) != EOF){
		putc(c,dest);
	}
}
int main(int argc, char *argv[]){
	FILE *dest, *src;
	char *program = argv[0];
	if((dest = fopen(*++argv,"a")) != NULL){
		while((src = fopen(*++argv,"r")) != NULL){
			fileappend(dest,src);
		}
	}
}
