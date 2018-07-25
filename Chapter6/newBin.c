#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "getCharTest.c"

#define MAXWORD 100

//binary tree implementation
struct node{
	char *word;
	int count;
	struct node *left;
	struct node *right;
	int depth;
};

int expo(int i){
	int result = 1;
	while(i-->0){
		result = result*2;
	}
	return result;
}

void NullNodelist(struct node *nlist[], int len){
	while(--len>=0){
		nlist[len] = NULL;
	}
}

void printTab(int num){
	while(num-->0){
		printf(" ");
	}
}
void printlayer(struct node *nodelist[],int start, int end,int tablen){

	struct node *p;
	for( ;start<end;start++){
		p = nodelist[start];
		if(p == NULL){
			printf("   ");
		}else{
			printf("(%s %d %d)",p->word,p->count,p->depth);		
		}
		if(start != end -1) printTab(tablen);
	}
}

int treeprint(struct node *p,int depth){ //depth distance from leave to current node
	int i, maxele = expo(depth+1), start, end;
	int tabCount = maxele, printlen = 1;
	struct node *nodelist[maxele];
	NullNodelist(nodelist,maxele);
	printf("maxele = %d \t depth = %d\n",maxele,depth);
	nodelist[1] = p;
	for(i = 0;i<depth+1;i++){
		start = expo(i);
		end = expo(i+1);
		printTab(tabCount/2);
		printlayer(nodelist,start, end,tabCount);
		if(i != depth){
			printlen *= 2;
			tabCount /= 2;
			//printf("start = %d\t end = %d\n",start,end);
			while( start< end){
				nodelist[2*start] =   (nodelist[start] == NULL) ? NULL: nodelist[start]->left;
				nodelist[2*start+1] = (nodelist[start] == NULL) ? NULL: nodelist[start]->right;
				start++;
			}			
		}
		printf("\n");
	}
	return 0;
}

struct node *nodeAlloc(){
	return (struct node *) malloc(sizeof(struct node));
}

void bookTreeprint(struct node *p){
	if(p != NULL){
		bookTreeprint(p->left);
		printf("(%s %d %d)",p->word,p->count,p->depth);	
		bookTreeprint(p->right);
	}
}
	
/*  depth[0] = tracked depth of individual node
	depth[1] = max depth of the tree
*/ 
struct node *addtree(struct node *p,char *w,int depth[2]){
	int cond;
	if(p == NULL){
		p = nodeAlloc();
		p->word = strdup(w);
		p->count = 1;
		p->left = (p->right = NULL);
		p->depth = depth[0];
		depth[1] = (depth[1] > depth[0]) ? depth[1] : depth[0];
	}else if((cond = strcmp(w,p->word)) == 0){ // this is the word
		p->count++;
	}else if(cond < 0){ //less than the word
		depth[0] += 1;
		p->left = addtree(p->left,w,depth);
	}else{
		depth[0] += 1;
		p->right = addtree(p->right,w,depth);
	}
	return p;
}

int getword(char *word, int lim){
	char *w = word;
	int c, cond = 1;
	while(isspace(c = getch()) || c == '\t' || c == '\n')
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
	char word[MAXWORD];
	int i;
	struct node *root;
	root = NULL;
	int depth[2] = {0,-1};
	while(getword(word,MAXWORD) != EOF){
		//printf("word: %s\n",word);
		if(isalpha(word[0])){
			depth[0] = 0;
			root = addtree(root,word,depth);
		}
	}
	printf("depth[0] = %d \t depth[1] = %d\n", depth[0], depth[1]);
	i = treeprint(root,depth[1]);
	//bookTreeprint(root);
	return 0;
}
