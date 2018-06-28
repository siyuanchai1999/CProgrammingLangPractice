#include <stdio.h>
#include <string.h>
#include <stdlib.h>



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


int numcmp(const char *a, const char *b){
	double va, vb;
	va = atof(a);
	vb = atof(b);
	return (int)(va - vb);
}

void swap(char *v[], int px, int py){
	char *temp = v[px];
	v[px] = v[py];
	v[py] = temp;
}

int partition(char *v[], int start,int end, int (*comp)(void *, void *)){
	char *pivot = v[end];
	int i = start-1, j = start;
	for(j = start;j<end;j++){
		if((*comp)(v[j],pivot)<0){
			swap(v,++i,j);
		}
	}
	swap(v,i+1,end);
	return i+1;
}



void quickSort(char *v[], int left, int right, int numeric){
	if(left<right){
		int x = partition(v,left,right,(int (*)(void*,void*))(numeric ? numcmp: strcmp));
		quickSort(v,left,x-1,numeric);
		quickSort(v,x+1 ,right,numeric);
	}
	
}

int main(int argc, char *argv[]){
	int nlines, numeric = 0;
	if(argc>1 && strcmp(argv[1], "-n") == 0){
		numeric = 1;
	}else if(argc >1){
		printf("Usage: qsort-updated [-n]\n");
	}
	
	if((nlines = readlines(lineptr, MAXLINES))>=0){
		quickSort(lineptr,0,nlines-1,numeric);
		writeLines(lineptr,nlines);
		//system("pause");
		return 0;
	}else{
		printf("error: input too big");
		return 1;
	}
} 
