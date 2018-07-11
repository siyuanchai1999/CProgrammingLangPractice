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

void copyNodeList(struct node *dest[], struct node *src[], int len){
	while(--len >= 0){
		dest[len] = src[len];
	}
}

void newNodelist(struct node *newlist[], struct node *back[],int len){
	int i = 0;
	while(i<len){
		if(back[i] != NULL){
			newlist[2*i] = (back[i])->left;
			newlist[2*i+1] = (back[i])->right;
		}else{
			newlist[2*i] = NULL;
			newlist[2*i+1] = NULL;
		}
		i++;
	}
}

void printTab(int num){
	while(num-->0){
		printf("  ");
	}
}
void printlayer(struct node *nodelist[],int len,int tablen){
	int i;
	struct node *p;
	for(i = 0;i<len;i++){
		p = nodelist[i];
		if(p == NULL){
			printf("  ");
		}else{
			printf("(%s %d)",p->word,p->count);		
		}
		if(i != len -1) printTab(tablen);
	}
}

int treeprint(struct node *p,int depth){ //depth distance from leave to current node
	/*if(p != NULL){
		treeprint(p->left);
		printf("(%4d %s %d\n)",p->count,p->word,p->depth);
		treeprint(p->right);
	}*/
	int i, maxele = expo(depth);
	int tabCount = 2*maxele - 1, printlen = 1;
	printf("maxele = %d\n",maxele); 
	struct node *nodelist[maxele];
	struct node *nodelistback[maxele];
	NullNodelist(nodelist,maxele);
	NullNodelist(nodelistback,maxele);
	nodelist[0] = p;
	
	for(i = 0;i<depth+1;i++){
		//printf("%d:",tabCount/2);
		printTab(tabCount/2);
		printlayer(nodelist,printlen,tabCount);
		//printf("printlen=%d\n",printlen);
		if(i != depth){
			copyNodeList(nodelistback,nodelist,printlen);
			newNodelist(nodelist,nodelistback,printlen);
			printlen *= 2;
			tabCount /= 2;
		}
		printf("\n");
	}
	printf("output finished\n");
	return 0;
}

struct node *nodeAlloc(){
	return (struct node *) malloc(sizeof(struct node));
}
	

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
	return 0;
}
