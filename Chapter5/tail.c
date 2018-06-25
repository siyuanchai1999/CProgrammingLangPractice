#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAXLINE 1000
#define MAXLINES 500
#define ALLOCSIZE 1000


//exercises 5-16
int getline(char *s, int lim){
	int c,i;
	i = 0;
	while(--lim>0 && (c=getchar())!= EOF && c !='\n'){
		*s++ = c;
		i++;
	}
	if(c == '\n') s[i++] = c;
	*s = '\0'; //str terminator 
	return i;
}

void writeLines(char *linep[], int nlines,int n){
	int i;
	printf("writeLines output:\n");
	for(i=nlines -n; i <nlines;i++){
		printf("%s\n",linep[i]);
	}
	printf("writeLines output finished\n");
	printf("-------------\n");
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

int charToInt(char *str){
	int c,result = 0;
	while(c = *str++ ){
		if(isdigit(c)){
			result = result*10 + (c-'0');	
		}else{
			return -1;
		}
	}
	return result;
}

int main(int argc, char*argv[]){
	char *lineptr[MAXLINES];
	char line[MAXLINE];
	int n = 3,c,len,lineno = 0;
	if(argc == 1){
		//all is right
	}else if(argc == 2 && (*++argv)[0] == '-'){
		if((c = charToInt(++argv[0]))!= -1){
			n = c;
		}else{
			printf("illegal parameter: %s",argv[0]);
			argc = 0;
		}	
	}else{
		printf("Usage: tail [-t]\n");
		argc = 0;
	}	
	char *allocPos;
	while((len = getline(line,MAXLINE)) >0 && argc!= 0 && (allocPos = alloc(len))){
				lineptr[lineno] = allocPos;
				strcpy(lineptr[lineno++],line);
		}
	if(allocPos){
		writeLines(lineptr,lineno,n);
	}else{
		printf("Error: input oversize\n");
	}
		
	return lineno;
}
