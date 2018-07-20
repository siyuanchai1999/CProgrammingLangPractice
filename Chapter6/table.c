#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define HASHSIZE 101
struct nlist{
	struct nlist *next;
	char *name;
	char *defn;
};

static struct nlist *hashtab[HASHSIZE];

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
			return np;			//found
		}
	}
	return NULL;		//not found
}

struct nlist *install(char *name, char *def){
	struct nlist *np;
	unsigned hashval;
	
	if((np = lookup(name)) == NULL){
		np = (struct nlist *) malloc(sizeof(*np));
		if(np == NULL || (np->name = strdup(name)) == NULL) return NULL;
		hashval = hash(name);
		np->next = hashtab[hashval];
		hashtab[hashval] = np;
	}else{
		free((void *) np->defn);
	}
	if((np->defn = strdup(def)) == NULL) return NULL;
	return np;
}

void printptr(struct nlist *p){
	printf("(%s, %s)\n",p->name,p->defn);
}

int main(){
	struct nlist *p;
	p = install("name","123");
	printptr(p);
	printptr(p->next);
	
}


