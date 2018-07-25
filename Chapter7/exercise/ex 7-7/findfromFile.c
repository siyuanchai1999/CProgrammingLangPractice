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

struct lineinfo{
	int linen;
	char *line;
	char *fname;
};

static struct file *fileArr[MAXFILE];
static struct lineinfo *lineArr[MAXLINES];
int Strcpy(char *dest, char *src){
	int len = 0;
	while(*dest++ = *src++)
		len++;
	*dest = '\0';
	return len;
}
char *fgetline(char *str, int max, FILE *ip){
	int c;
	char *s = str;
	
	while(--max > 0 && (c = getc(ip)) != EOF){
		if( c == '\n'){
			break;
		}else{
			*s++ = c;
		}
	}
	*s = '\0';
	return (c == EOF && s == str) ? NULL : str;  		//all characters has been read
}

void writeLines(int len, int number){
	int i;
	char *pre = NULL;
	printf("filename  \t");
	if(number) printf(" linenum \t");
	printf(" content\n");
	
	for(i= 0;i<len;i++){
		if(lineArr[i]->fname != pre){
			printf("%-10s\t ",pre = lineArr[i]->fname);
		}else{
			printf("          \t ");
		}
		if(number) printf("%-9d\t ",lineArr[i]->linen);
		printf("%s\n",lineArr[i]->line);
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

void outputfiles(int len){
	int i;
	for(i = 0; i<len;i++){
		printf("%d\t%s\n",i,fileArr[i]->name);
	}
}

int main(int argc, char*argv[]){
	FILE *fp;
	char line[MAXLINE];
	
	char *pattern,*prog = *argv;
	int found = 0, except = 0, number = 0,c;
	int lineno = 0, filenum = 0;
	while(--argc >0 && (*++argv)[0] == '-'){
		while(c = *++argv[0]){
			//printf("c:%c",c);
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
		//printf("pattern = %s\n",pattern);
		while(--argc > 0){
			if((fp = fopen(*argv,"r")) != NULL){
				fileArr[filenum] = (struct file *) malloc(sizeof(struct file));
				fileArr[filenum]->fptr = fp;
				fileArr[filenum++]->name = *argv++;
			}else{
				printf("%s: cannot find %s\n",prog,*argv++);
			}
		}
		
		//printf("files paramater done\n");
		if(filenum == 0){
			char str2[6] = "stdin";
			fileArr[filenum] = (struct file *) malloc(sizeof(struct file));
			fileArr[filenum]->fptr = stdin;
			fileArr[filenum]->name = alloc(strlen(str2)+1);
			Strcpy(fileArr[filenum++]->name,str2);
			printf("sdtin assigned\n");
		}
		//outputfiles(filenum);
		int i = 0;
		while(i<filenum){
			lineno = 0;
			while(fgetline(line,MAXLINE,fileArr[i]->fptr) != NULL){
				lineno++;
				if(found < MAXLINES && (strstr(line,pattern) != NULL) != except){
					lineArr[found]= (struct lineinfo *) malloc(sizeof(struct lineinfo));
					lineArr[found]->linen = lineno;
					lineArr[found]->fname = fileArr[i]->name;
					lineArr[found]->line  = (char *) malloc(strlen(line)+1);
					strcpy(lineArr[found++]->line,line);
				}
			}
			fclose(fileArr[i++]->fptr);
		}
		writeLines(found,number);
		
	}
	

	return found;
}
