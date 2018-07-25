#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "getCharTest.c"

#define MAXWORD 50
#define MAXWORDS 1000
#define OCCUR 50
#define BUFFERSIZE 1000


char buffer[BUFFERSIZE];
char *bufferptr = buffer;
char *alloc(int len){
	if(bufferptr - buffer + len < BUFFERSIZE){
		//printf("bufferptr = %d\tbuffer = %d\n",bufferptr,buffer);
		
		bufferptr += len;
		return bufferptr - len;
	}else{
		printf("storage not enough!!\n");
		return NULL;
	}
}

void afree(char *p){
	if(p> buffer && p< buffer + BUFFERSIZE){
		bufferptr = p;
	}
}


struct node{
	char *string;
	int ocurrence;
	int index;
	struct node *left;
	struct node *right;
};
struct node *nodelist[MAXWORDS];
int maxlen = 0;
struct node *nodeAlloc(){
	return (struct node *) malloc(sizeof(struct node));
}



struct node *addtree(struct node *p, char *word, int curIndex){
	int cond = 0;
	 
	if(p == NULL){
		p = nodeAlloc();			//construct the new node
		p->string = strdup(word);
		p->ocurrence = 1;
		p->index = curIndex;
		p->left = NULL;
		p->right = NULL;
		
		nodelist[curIndex] = p;								//update nodelist
		maxlen = (maxlen < curIndex) ? curIndex : maxlen;
	}else if((cond = strcmp(word,p->string)) == 0){
		p->ocurrence++;
	}else if(cond>0){
		p->right = addtree(p->right,word,p->index*2 +1);
	}else{
		p->left  = addtree(p->left,word,p->index*2);
	}
	return p;
}

void nodePrint(struct node *p){
	printf("(%s  %d  %d)",p->string,p->ocurrence, p->index);
}

void listPrint(){
	int i;
	printf("maxlen= %d\n",maxlen);
	for(i = 1;i<=maxlen;i++){
		if(nodelist[i] != NULL ){
			nodePrint(nodelist[i]);
			printf("\t");	
		}
	}
}

int nodecmp(struct node *p, struct node *q){
	if(p == NULL && q == NULL){
		return 0;
	}else if(p == NULL){
		return -1;
	}else if(q == NULL){
		return 1;
	}else{
		return p->ocurrence - q->ocurrence;
	}
}

void swap(struct node *nodelist[], int a, int b){
	struct node *temp = nodeAlloc();
	temp = nodelist[a];
	nodelist[a] = nodelist[b];
	nodelist[b] = temp;
}

int partition(struct node *nodelist[],int start, int end){
	struct node *pivot = nodelist[end];
	int i = start - 1, j;
	for(j = start;j<end; j++){
		if(nodecmp(nodelist[j],pivot)>0){
			swap(nodelist,++i,j);
		}
	}
	swap(nodelist,i+1,end);
	return i+1;
}

void nodeQsort(struct node *nodelist[],int start, int end){
	if(start < end){
		int mid = partition(nodelist,start,end);
		nodeQsort(nodelist,start,mid-1);
		nodeQsort(nodelist,mid+1,end);
	}
}

void treeprint(struct node *p){
	if(p != NULL){
		treeprint(p->left);
		printf("(%s %d)",p->string,p->ocurrence);
		treeprint(p->right);
	}
} 

int getword(char *word, int lim){
	char *w = word;
	int c, cond = 1;
	while( (c = getch()) == '\n' && isspace(c) )
		;
		
	if(!isalpha(c)){
		*w = '\0';
		return c;
	}else{
		*w++ = c;
	}
	while(--lim> 0 && cond){
		c = getch();
		if(isalnum(c)){
			*w++ = c;
		}else{
			ungetch(c);
			cond = 0;
		}
	}
	*w = '\0';
	return word[0];		
}

int main(){
	char *word = alloc(MAXWORD);
	int c, lineN = 1, len = 0;
	struct node *root = NULL;
	
	while((c = getword(word,MAXWORDS) )!= EOF){
		 if(isalpha(word[0])){
			root = addtree(root,word,1);
		}
	}
	
	nodeQsort(nodelist,1,maxlen);
	listPrint();
}
