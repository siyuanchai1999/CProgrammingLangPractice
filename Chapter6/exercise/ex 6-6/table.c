#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#include "getCharTest.c"

#define HASHSIZE 101
#define MAXWORD 50
struct nlist{
	struct nlist *next;
	char *name;
	int val;
};

static struct nlist *hashtab[HASHSIZE];


int getword(char *word, int lim){
	char *w = word;
	int c, cond = 1;
	while( (c = getch()) == '\n' || isspace(c) )
		;
		
	if(!isalnum(c) && c != '#' && c != '-'){
		*w = '\0';
		return c;
	}else{
		*w++ = c;
	}
	
	while(--lim> 0 && cond){
		c = getch();
		if(isalnum(c) || c == '#'){
			*w++ = c;
		}else{
			ungetch(c);
			cond = 0;
		}
	}
	*w = '\0';
	return word[0];		
}

int str2int(char *s){
	int result = 0;
	while(isdigit(*s)){
		result = result *10 + (*s - '0');
		*s++;
	}
	return result;
}

unsigned hash(char *s){
	unsigned hashval;
	for(hashval = 0;*s != '\0';s++){
		hashval = *s + hashval * 31;
	}
	return hashval%HASHSIZE;
}

struct nlist *lookup(char *s){
	struct nlist *np;
	for(np = hashtab[hash(s)]; np != NULL; np = np->next ){
		if(strcmp(s,np->name) == 0){
			return np;		//found
		}
	}
	return NULL;		//not found
}

// *err = 1 structure storage not enough
// *err = 2 char storage not enough
struct nlist *install(char *name, int def, int *err){
	*err = 0;
	struct nlist *np;
	unsigned hashval;
	if((np = lookup(name)) == NULL){
		np = (struct nlist *) malloc(sizeof(*np));
		if(np == NULL){
			*err = 1;
			return NULL;
		}
		if((np->name = strdup(name)) == NULL){
			*err = 2;
			return NULL;	
		}
		hashval = hash(name);
		np->next = hashtab[hashval];
		hashtab[hashval] = np;
	}
	np->val = def;
	return np;
}


struct nlist *undef(char *name){
	struct nlist *np;
	unsigned hashval;
	if((np = lookup(name)) != NULL){
		hashtab[(hashval = hash(name))] = np->next; 
		free((void *) np->name);
	}else{
		printf("no table entry named %s was found\n",name);
	}
}

void printptr(struct nlist *p){
	printf("(%s, %d)\n",p->name,p->val);
}

void waitNextLine(){
	char c;
	while((c = getch()) != '\n' && c != EOF)
		;//printf("c = %d %c",c,c);	
	ungetch(c);
}


int main(){
	struct nlist *p;
	char word[MAXWORD], temp[MAXWORD];
	char *wordptr[MAXWORD];
	int c,cond,neg = 1,val,err;
	
	while((c = getword(word, MAXWORD)) != EOF ){
//		printf("word: %s %d %d \n",word, word[0] == '#',strcmp(word,"#define") == 0);
		if(word[0] == '#' && strcmp(word,"#define") == 0){
			c = getword(word,MAXWORD);
			//printf("name: %s\n",word);
			if(isalnum(word[0])){
				strcpy(temp,word);
				c = getword(word,MAXWORD);
				if(isdigit(word[0])){
					val = str2int(word);
					printf("(%s %d)\n",temp,val);
					install(temp,val,&err);
				}else if(word[0] == '-'){
					val = str2int(&word[1]) * (-1);
					printf("(%s %d)\n",temp,val);
					install(temp,val,&err);
				}else{
					printf("invalid number %s\n",word);
				}
				waitNextLine();
			}else{
				printf("invalid name: %s\n",word);
				waitNextLine();
			}	
		}else{
			printf("#define keyword err\n");
			waitNextLine();
		}
	}
	printf("HASHSIZE %d\n",lookup("HASHSIZE")->val);
	printf("MAXWORD  %d\n",lookup("MAXWORD")->val);
}


