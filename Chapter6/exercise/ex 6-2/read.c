#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "getCharTest.c"
#define MAXWORD 50

struct node{
	char *string;
	struct node *downLeft;
	struct node *downRight;
	int len;
	int occurrence;
	struct node *left;
	struct node *right;
};

int strcmpPre(char *str1, char *str2, int num){
	while(num-->0){
		if(*str1 != *str2) return *str1 - *str2;
		str1++;
		str2++;
	}
	return 0;
}

struct node *addtree(struct node *p,char *word,int num){
	int downCond, forwCond;
	if(p == NULL){
		p = (struct node *) malloc(sizeof(struct node));
		p->string = strdup(word);
		p->len = 1;
		p->occurrence = 1;
		p->downLeft = NULL;
		p->downRight = NULL;
		p->left = NULL;
		p->right = NULL;
		
	}else if((downCond = strcmpPre(word,p->string,num)) == 0){
		p->len++;
		if((forwCond = strcmp(word,p->string) ) == 0){
			p->occurrence++; 		//this is the case
		}else if(forwCond < 0){
			p->downLeft = addtree(p->downLeft,word,num);
			//printf("%s was added to the downleft of %s\n",word,p->string);
		}else{
			p->downRight = addtree(p->downRight,word,num);
			//printf("%s was added to the downright of %s\n",word,p->string);
		}
	}else if(downCond < 0){
		p->left = addtree(p->left,word,num);
		//printf("%s was added to the left of %s\n",word,p->string);
	}else{
		p->right = addtree(p->right,word,num);
		//printf("%s was added to the right of %s\n",word,p->string);
	}
	return p;
}

void downPrint(struct node *p){
	if(p != NULL){
		downPrint(p->downLeft);
		printf("%s\t",p->string);
		downPrint(p->downRight);
		
	}
}

void forwPrint(struct node *p){
	if(p!= NULL){
		forwPrint(p->left);
		downPrint(p);
		printf("\n");
		forwPrint(p->right);
	}
}

int getword(char *word, int lim){
	char *w = word;
	int c, cond = 1;
	while(isspace(c = getch()) || c == '\t' || c == '\n')
		;
	if(!isalpha(c)){
		*w = '\0';
		if(c == '/'){
			if((c = getch()) == '/'){
				while((c = getch()) != '\n')
					;
			}else if(c == '*'){
				int d;
				while(!((c = getch() )== '*' && (d = getch()) == '/'))
					;	
			}else{
				ungetch(c);
			}
		}
		if( c == '"'){
			while((c = getch()) != '"')
				;
		}
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

int tryFindNum(char *str){
	//printf("%s",str);
	int result;
	while(isdigit(*str)){
		result = result*10 + (*str++ - '0');
	}
	if(*str != '\0'){
		printf("illegal para: %c\n",*str);
		return -2; //error
	}else{
		return result;
	}
}

int main(int argc, char *argv[]){
	int num = -1 , nflag = 0, c,neg = 0,cont = 1;
	while(--argc>0 && (  (isdigit(c = **(++argv)) && nflag) || (!nflag && c == '-') ) ){
		neg = (!nflag && c == '-') ? -1:1;
		while(cont == 1 && (c = ((nflag && isdigit(c)) ? c:*++argv[0]) ) ){
			switch(c){
				case 'n':
					nflag = 1;
					break;
				default:
					if(nflag && isdigit(c)){
						cont = 0;
						num = tryFindNum(*argv) * neg;
						if(num<0) argc = -1;
						break;
					}
					neg = 0;
					printf("usage: read [-n num]\n");
					argc = -1;
					break;
			}
		}
	}
	printf("test output\n");
	
	if(c == '-' && nflag){
		printf("usage: read [-n num(nonnegative)]\n");
	}else if(num< 0 && nflag){
		num = 6;
	}
	if(nflag == 0) num = 6;
	printf("num = %d \t nflag = %d argc = %d\n",num,nflag,argc);
	
	if(argc == 0){
		char word[MAXWORD];
		struct node *root = NULL;
		while(getword(word,MAXWORD) != EOF){
			//printf("word: %s\n",word); 
			if(isalpha(word[0])){
				root = addtree(root,word,num);
			}
		}
		forwPrint(root);
	}
	//printf("done\n");
	
}
