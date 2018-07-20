#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAXLINE 1000
#define MAXLINES 500
#define ALLOCSIZE 1000
#define MAXFILE 10

/*
find pattern from files or stdin

*/
struct file{
	char *name;
	FILE *fptr;
};

static struct file *fileArr[MAXFILE];

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

void writeLines(char *linep[], int nlines){
	int i;
	printf("writeLines output:\n");
	for(i=0; i<nlines;i++){
		printf("%s\n",linep[i],*(linep[i]+10));
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

char *pitoa(int num,char *str){

	while(num>0){
		*str++ = num %10 +48;
		num = num/10;
	}
	*str++ = ' ';
	*str++ = ':';
	*str++ = ' ';
	*str = '\0';
	return str;
}

void outputfiles(int len){
	int i;
	for(i = 0; i<len;i++){
		printf("%d\t%s\n",i,fileArr[i]->name);
	}
}

int main(int argc, char*argv[]){
	FILE *fp;
	char *lineptr[MAXLINES];
	char lineNum[100];
	char line[MAXLINE];
	char *pattern,*prog = *argv;
	int found = 0, except = 0, number = 0,c;
	int lineno = 0, filenum = 0;
	while(--argc >0 && (*++argv)[0] == '-'){
		while(c = *++argv[0]){
			printf("c:%c",c);
			switch(c){
				case 'x':
					except = 1;
					break;
				case 'n':
					number = 1;
					break;
				default:
					printf("illegal parameters %c\n",c);
					argc = 0;
					found = -1;
					break;
			}
		}
	}
	printf("except:%d \t number:%d\t argc:%d\n",except,number,argc);
	
	if(argc < 1){
		printf("usage: find [-n][-x] pattern [files...]\n");
	}else{
		pattern = *argv++;
		printf("pattern = %s\n",pattern);
		while(argc-- > 0){
			if((fp = fopen(*argv,"r")) != NULL){
				fileArr[filenum] = (struct file *) malloc(sizeof(struct file));
				fileArr[filenum]->fptr = fp;
				fileArr[filenum++]->name = *argv++;
			}else{
				printf("%s: cannot find %s\n",prog,*argv++);
			}
		}
		outputfiles(filenum);
		
	}
	
	/*
	if(argc	 != 1){
		printf("Usage: find [-x] [-n] pattern\n");
	}else{
		while(getline(line,MAXLINE) >0 ){
			lineno++;
			if( (strstr(line,*argv) != NULL) != except){
				if(number){
					itoa(lineno,lineNum);
					strcat(lineNum,line);
					strcpy(line,lineNum);
				}
				lineptr[found] = alloc(strlen(line)+1);
				strcpy(lineptr[found++],line);
			}
		}
		writeLines(lineptr,found);
	}*/
	return found;
}
