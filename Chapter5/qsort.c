#include <stdio.h>
#include <string.h>

#define MAXLINES 1000
#define MAXLEN 500

char *lineptr[MAXLINES];
int getline(char s[], int lim){
	int c,i;
	i = 0;
	while(--lim>0 && (c=getchar())!= EOF && c !='\n'){
		s[i++] = c;
	}
	if(c == '\n') s[i++] = c;
	s[i] = '\0'; //str terminator 
	return i;
}

int readlines(char *linep[], int max){
	int len, nlines=0;
	char *p, line[MAXLEN];
	while((len = getline(line, MAXLEN)) >0){
		printf("len:%d\n",len);
		if(nlines>= max){
			return -1;
		}else{
			line[len - 1] = '\0';
			//p = line;
			//strcpy(p,line);
			printf("%s\n",line);
			lineptr[nlines] = line;
			printf("linep[%d]:%s\n",nlines,linep[nlines]);
			//if(nlines==1) printf("linep[%d]:%s\n",nlines-1,linep[nlines-1]);
			nlines++;
		}
	}
	return nlines;
}

void writelines(char *linep[], int nlines){
	int i;
	for(i=0; i<nlines;i++){
		printf("line%d:%s\n",i,linep[i]);
	}
}

void qsort(char *v[], int left, int right){
	
}

int main(){
	int nlines;
	if((nlines = readlines(lineptr, MAXLINES))>=0){
		printf("nlines:%d\n", nlines);
		printf("linep[0]:%s\n",lineptr[0]);
		printf("linep[1]:%s\n",lineptr[1]);
		//qsort(lineptr, 0,nlines);
		writelines(lineptr,nlines);
		return 0;
	}else{
		printf("error: input too big");
		return 1;
	}
} 
