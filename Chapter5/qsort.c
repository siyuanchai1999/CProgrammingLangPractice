#include <stdio.h>
#include <string.h>


#define MAXLINES 1000
#define MAXLEN 500
#define ALLOCSIZE 1000

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


void writeLines(char *linep[], int nlines);
char *lineptr[MAXLINES];
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

int readlines(char *lineptr[], int max){
	int len, nlines=0;
	char *p, line[MAXLEN];
	while((len = getline(line, MAXLEN)) >0){
		if(nlines>= max){
			return -1;
		}else{
			printf("len:%d",len);
			line[len - 1] = '\0';
			lineptr[nlines] = alloc(len);
			strcpy(lineptr[nlines++],line);
		}
		//writeLines(lineptr,nlines);
	}
	return nlines;
}

void writeLines(char *linep[], int nlines){
	int i;
	printf("writeLines output:\n");
	for(i=0; i<nlines;i++){
		printf("line%d: %s\n",i,linep[i]);
	}
	printf("writeLines output finished\n");
	printf("-------------\n");
}

void swap(char *v[], int px, int py){
	char *temp = v[px];
	v[px] = v[py];
	v[py] = temp;
}

int partition(char *v[], int start,int end){
	char *pivot = v[end];
	int i = start-1, j = start;
	for(j = start;j<end;j++){
		if(strcmp(v[j],pivot)<0){
			swap(v,++i,j);
		}
	}
	swap(v,i+1,end);
	return i+1;
}



void qsort(char *v[], int left, int right){
	if(left<right){
		int x = partition(v,left,right);
		qsort(v,left,x-1);
		qsort(v,x+1 ,right);
	}
	
}

int main(){
	int nlines;
	if((nlines = readlines(lineptr, MAXLINES))>=0){
		printf("input before sort:\n");
		writeLines(lineptr,nlines);
		qsort(lineptr,0,nlines-1);
		
		printf("input after sort:\n");
		writeLines(lineptr,nlines);
		system("pause");
		return 0;
	}else{
		printf("error: input too big");
		return 1;
	}
} 
