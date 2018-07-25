#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "quickSortM.c"

#define MAXLINES 1000
#define MAXLEN 500
#define ALLOCSIZE 10000
#define intSize 1000
#define PARTITION 9


static int intAllocbuf[intSize];
static int *intAllocp = intAllocbuf;

int *intAlloc(int n){
	if(intAllocp - intAllocbuf + n <=  intSize){
		intAllocp += n;
		return intAllocp - n;
	}else{
		return 0;
	}
}

void intFree(int *p){
	if(p>intAllocbuf && p<intAllocbuf + intSize){
		intAllocp  = p;
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
	while((len = getline(line, MAXLEN)) >0 && nlines>= 0){
		if(nlines>= max){
			return -1;
		}else{
			line[len - 1] = '\0';
			if(!(lineptr[nlines] = alloc(len))) return -1;
			strcpy(lineptr[nlines++],line);
		}
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


int numcmp(const char *a, const char *b,int conList[]){
	double va, vb;
	va = atof(a);
	vb = atof(b);
	return (int)(va - vb);
}

char getNextDir(const char *str){
	char result = *str++;
	while(!(isalpha(result) || isdigit(result) || isspace(result))){
		result = *str++;
	}
	return result;
}

int strCmp(const char *str1, const char *str2, int conList[]){
	char a,b;
	do{
		a = conList[3]? (getNextDir(str1++)): *str1++; 
		b = conList[3]? (getNextDir(str2++)): *str2++; 
		a = (a>'A' && a<'Z'&& conList[2]) ? (a + 'a' - 'A') : a;
		b = (b>'A' && b<'Z'&& conList[2]) ? (b + 'a' - 'A') : b;
	}while(a && b && a==b);

	return a - b;
}

void clearConList(int conList[],int pos){
	int i = 0;
	for(i =0; i<pos;i++){
		conList[i] = 0;
	}
}	

void showConList(int conList[]){
	int i = 0;
	while(i<storageLen){
		if(conList[i] != -1) printf("conList[%d]: %d\t",i,conList[i]);
		i++;
	}
	printf("\n");
}


void swap(char *v[], int px, int py){
	char *temp = v[px];
	v[px] = v[py];
	v[py] = temp;
}

int partition(char *v[], int start,int end, int (*comp)(void *, void *, int[]),int conList[]){
	char *pivot = v[end];
	int i = start-1, j = start;
	for(j = start;j<end;j++){
		if(conList[1]){
			if((*comp)(v[j],pivot,conList)>0){
				swap(v,++i,j);
			}
		}else{
			if((*comp)(v[j],pivot,conList)<0){
				swap(v,++i,j);
			}
		}
		
	}
	swap(v,i+1,end);
	return i+1;
}



void quickSort(char *v[], int left, int right, int conList[]){
	if(left<right){
		int x = partition(v,left,right,
		(int (*)(void*,void*,int[]))(conList[0] ? numcmp: strCmp),
		conList); //numeric
		quickSort(v,left,x-1,conList);
		quickSort(v,x+1 ,right,conList);
	}
	
}

int checkPreDef(int infoTable[][width], int conList[], int cur,int j){
	int start = conList[cur], end = conList[cur+1];
	while(--j> 0){
		if(start == infoTable[j][0] && end == infoTable[j][1]) return j;
	}
	return 0;
}

int index2exp(int p){
	int result = 1;
	while(p-->0){
		result *= 10;
	}
	return result;
}

int checkExp(int val,int check){
	return (val/index2exp(check))  % 10;
}
 
int redoconList(int conList[], int infoTable[][width]){
	int i,j =1,p;

	for(i=10 ;i<storageLen;i+=2){
		if(conList[i] != -1 && conList[i+1] != -1){
			if(!(p = checkPreDef(infoTable,conList,i,j))){
				//printf("not found: p = %d \t i=%d \t j=%d\n",p,i,j);
				infoTable[j][0] = conList[i];
				infoTable[j][1] = conList[i+1];
				infoTable[j++][2] += index2exp((i-10)/2);
				//showMatrix(infoTable);
			}else{
				//printf("found: p = %d \t i=%d \t adder: %d\n",p,i,index2exp((i-10)/2));
				infoTable[p][2] += index2exp((i-10)/2);
			}
			infoTable[0][0] = 1;
		}	
	}
//	showMatrix(infoTable);
	return j;
}

void initTable(int table[PARTITION][width], int conList[]){

	int i,j;
	for(i = 0; i<PARTITION;i++)	{
		for(j=0;j<width;j++){
			table[i][j] = -1;
		}
	}
	table[0][0] = 0;
	i = 0;
	while(i++<PARTITION){
		table[i][width-1] = 0;
	}

	//printf("initialization done\n");
}

int checkTableVal(int table[PARTITION][width],int conList[],int len){
	int val,j;
	if(table[0][0] == 1){
		while(--len>0){							//check compatibility within partition
			val = table[len][width-1];
			if( checkExp(val,0) && checkExp(val,2)){
				printf("-n not compatible with -f\n");
				return 0;
			}else if(checkExp(val,0) && checkExp(val,3)){
				printf("-n not compatible with -d\n");
				return 0;
			}
		}
		
		for(len = 1; table[len][0] != -1;len++){   //check intersection
			for(j = len+1; table[j][0] != -1;j++){
				if(table[len][0]< table[j][0] && table[len][1]< table[j][0]){
				}else if(table[len][0]> table[j][0] && table[len][0] > table[j][1]){
				}else{
					printf("intersection of partition not allowed, plz check partition");
					return 0;
				}
			}
		}
	}else{
		if(conList[0] && conList[2]){			//check compatibility without partition
			printf("-n not compatible with -f\n");
			return 0;
		}else if(conList[0] && conList[3]){
			printf("-n not compatible with -d\n");
			return 0;
		}
	}
	return 1;
}

void fixTable(int table[PARTITION][width], int nlines, int len){
	while(--len>0){
		if(table[len][1]>nlines){
			printf("table[%d][1] changes from %d to %d\n",len,table[len][1], nlines -1);
			table[len][1] = nlines - 1;
		}
	}
}

void list2Str(char *str, int *list, int len){
	int i = 0;
	while(i<len){
		if(*(list+i)){
			if(i==0) *str++ = 'n';
			else if(i==1) *str++ = 'r';
			else if(i==2) *str++ = 'f';
			else if(i==3) *str++ = 'd';
		}
		i++;
	}
	*str = '\0';
}


void superQsort(char *lineptr[], int table[PARTITION][width], int conList[], int nlines, int len){
	int i,varNum = 4;
	if(table[0][0]){
		int *List = intAlloc(varNum);
		char *para = alloc(varNum+1);
		while(--len>0){
			for(i = 0; i<varNum;i++){
				List[i] = checkExp(table[len][2],i);
			}
			list2Str(para,List,varNum);
			printf("qsort from %d to %d with parameter -%s\n",table[len][0],table[len][1],para);
			quickSort(lineptr,table[len][0], table[len][1],List);
		}
		intFree(List);
	}else{
		int start = 0, end = nlines -1;
		for(i = 4; i<storageLen && conList[i] != -1 && conList[i+1] != -1;i +=2){
			start = conList[i];
			end   = conList[i+1];
			printf("going qsort from %d to %d\n",start, end);
			quickSort(lineptr,start,end,conList);
		}
		if(start == 0 && end == nlines -1){
			printf("going qsort from %d to %d\n",start, end);
			quickSort(lineptr,start,end,conList);
		}

	}
}


int tryFindPos(char *str, int conList[], int para){
	int start = 0, end =0;
	while(isdigit(*str)){
		start = start*10 + (*str++ - '0');
	}
	if(*str == ':'){
		str++;
		while(isdigit(*str) ){
			end = end*10 + (*str++ - '0');
		}
	}else if(isdigit(*str)){
		printf("err parameters: %c\n",*str);
		return -1;
	}
	if(start<= end && para <4){
		conList[2*para+10] = start;  //specific option field
		conList[2*para+11] = end;
	}else if(start<= end && para >= 4 && para < storageLen-1){
		conList[para] = start;
		conList[para+1] = end;
	}else if(para >= storageLen){
		printf("err: exceed max num of partition!!\n");
		return -1;
	}
	return para;
}

int checkEmpty(int conList[]){
	int i = 0;
	for(i = 0;i<storageLen;i++){
		//printf("i = %d\t",i);
		if(conList[i] != ((i<4)? 0:-1)) return 0; 
		i = (i==3)? 9:i;
	}
	return 1;
}

int findPara(int conList[]){
	int i = 4;
	while(conList[i] != -1 && conList[i+1] != -1){
		i += 2;
		if(i == 10) i = 18;
	}
	return i;
}

/****
conList [0] = numeric;     [10] = numeric startPos,   [11] numeric endPos
		[1] = reverse;	   [12] = reverse startPos,   [13] reverse endPos
		[2] = fold;	 	   [14] = fold startPos,      [15] fold endPos
		[3] = directory;   [16] = directory startPos, [17] directory endPos
		[4] = normal startPos, [5] = normal endPos

*/

int main(int argc, char *argv[]){
	int nlines, numeric = 0, reverse = 0,fold = 0,directory = 0,c,found=-1;
	int *conList = intAlloc(storageLen);
	for(c = 0;c<storageLen;c++){ //initialize the conlist
		conList[c] = (c<4)? 0:-1;
	}
	while(--argc>0   &&   (((c = *(*++argv))== '-') || isdigit(c))){ //equivalent to (*++argv)[0]
		while( (c = (isdigit(c)) ? c:*(*argv)++ ) && found == -1){  //if c is digit just get itself; if not get -f or -n stuff
			//printf("c:%c\t found = %d\n",c,found);
			switch(c){
				case '-':
					//nothing all is right;
					clearConList(conList,4); //conList is used to indicate which parameter needs field definition
											 // const like numeric etc. is used to store them temprorary
					break;
				case 'n':
					conList[0] = 1;
					numeric = 1;
					break;
				case 'r':
					conList[1] = 1;
					reverse = 1;
					break;
				case 'f':
					conList[2] = 1;
					fold = 1;
					break;
				case 'd':
					conList[3] = 1;
					directory = 1;
					break;
				default:
					if(isdigit(c)){
					//showConList(conList);
						for(c=0;c<4;c++){
								if(conList[c]  && found == -1){
									found = tryFindPos(*argv,conList,c);
								}else if(conList[c] && found != -1){  //not bother to go throught the loop again!!
									conList[2*c + 10] = conList[2*found + 10];
									conList[2*c + 11] = conList[2*found + 11];
								}
						}
						if(checkEmpty(conList))
							//printf("empty!!!\n");
							found = tryFindPos(*argv,conList,findPara(conList));
						
						break;
					}else{
						printf("illegal parameters: %c\n",c);
						argc = -1;
						break;
					}
					break;
			}
			
		}
		found = -1;

	}
	 
	conList[0] = numeric;  //give values back to conList
	conList[1] = reverse;
	conList[2] = fold;
	conList[3] = directory;

	printf("\nnumeric:%d \t\t\t reverse:%d\t\t\t fold:%d\t\t\t directory:%d\t\t argc:%d\n",conList[0],conList[1], conList[2], conList[3],argc);
	
	int infoTable[PARTITION][width];
	initTable(infoTable,conList);
	//showConList(conList);
	int partLen = redoconList(conList,infoTable);
	
	if(argc<0){
		printf("Usage:qsort-updated [-r][-n][-f][-d]\n");
	}else if(!checkTableVal(infoTable,conList,partLen)){
		printf("nothing to do hhaha\n");
	}else{
		if((nlines = readlines(lineptr, MAXLINES))>=0){
			fixTable(infoTable,nlines,partLen);
			superQsort(lineptr,infoTable,conList,nlines,partLen);
			writeLines(lineptr,nlines);
			//system("pause");
			return 0;
		}else{
			printf("error: input too big");
			return 1;
		}
	}
} 
