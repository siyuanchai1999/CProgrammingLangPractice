#include <stdio.h>
#include <string.h>

#define MAXLINE 1000
#define MAXLINES 500
#define ALLOCSIZE 1000



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

char *itoa(int num,char *str){

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

int main(int argc, char*argv[]){
	char *lineptr[MAXLINES];
	char lineNum[100];
	char line[MAXLINE];
	int found = 0, except = 0, number = 0,c;
	int lineno = 0;
	while(--argc >0 && (*++argv)[0] == '-'){
		while(c = *++argv[0]){
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
	printf("except:%d \t number:%d\n",except,number);
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
//				printf("%s %d %d\n",line,strlen(line),*(line+strlen(line)));
				strcpy(lineptr[found++],line);
				//printf("found ++\n");
			}
		}
		writeLines(lineptr,found);
	}
	return found;
}
