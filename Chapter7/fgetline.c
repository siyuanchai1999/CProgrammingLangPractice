#include <stdio.h>

char *fgetline(char *str, int max, FILE *ip){
	int c;
	char *s = str;
	
	while(--max > 0 && (c = getc(ip)) != EOF){
		if((*s++ = c) == '\n') break;
	}
	*s = '\0';
	return (c == EOF && s == str) ? NULL : str;  		//all characters has been read
}

int fputline(char *str, FILE *op){
	int c;
	
	while(c = *str++){
		putc(c, op);
	}
	return ferror(op) ? EOF : 0;
}

int main(int argc, char *argv[]){

}
