
//pointer version of finding C keywords 
#include <stdio.h>
#include <string.h>
#include "getCharTest.c"

#define NKEYS 32
#define MAXWORD 100
struct key{
	char *word;
	int count;
}keytab[NKEYS] = {
	{"auto",0},
	{"break",0},
	{"case",0},
	{"char",0},
	{"const",0},
	{"continue",0},
	{"default",0},
	{"do",0},
	{"double",0},
	{"else",0},
	{"enum",0},
	{"extern",0},
	{"float",0},
	{"for",0},
	{"goto",0},
	{"if",0},
	{"int",0},
	{"long",0},
	{"register",0},
	{"return",0},
	{"short",0},
	{"signed",0},
	{"sizeof",0},
	{"static",0},
	{"struct",0},
	{"switch",0},
	{"typedef",0},
	{"union",0},
	{"unsigned",0},
	{"void",0},
	{"volatile",0},
	{"while",0}
} ;

struct key *binSearch(char *word, struct key *tab, int len){
	struct key *low = &tab[0];
	struct key *high = &tab[len -1];
	int cond;
	struct key *mid;
	while(low <= high){					//cannot be low < high; otherwise on-edge element will not be checked
		mid = low + (high - low)/2;
		if((cond = strcmp(word,mid->word)) > 0){
			low = mid + 1;	
		}else if(cond < 0){
			high = mid - 1;
		}else{
			return mid;
		}
	}
	return NULL;
}

int getWord(char *word, int lim,int comment){
	char *w = word;
	int c, cond = 1;
	while(isspace(c = getch()) || c == '\t' || c == '\n')
		;
	if(!isalpha(c)){
		//printf("c = %d %c\n",c,c);
		*w = '\0';
		if(comment && c == '/'){
			//printf("next: %d %c\n",ungetch(getch()), ungetch(getch()));
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

int main(int argc, char *argv[]){
	int p;
	struct key *x = &keytab[0];
	struct key *y = &keytab[1];
	printf("%d %s, %d %s",x,x->word,y,(x+1)->word);
	int comment = 0,c;
	while(--argc>0 && **(++argv) == '-'){
		while(c = *++argv[0]){
			switch(c){
				case 'c':
					comment = 1;
					break;
				default:
					printf("Usage: arrOfStruct [-c]\n");
					argc = -1;
					break;
			}
		}
	}
	
	if(argc == 0){
		//printf("comment = %d\n",comment);
		struct key *i;
		struct key *n;
		char word[MAXWORD];
		
		while(getWord(word,MAXWORD,comment) != EOF){				//read in and update the table
			//printf("word: %s\n",word);
			if(isalpha(word[0])){
				if((n = binSearch(word,keytab,NKEYS)) != NULL){
					n->count++;
				}
			}
		}
		
		for(i = keytab;i<keytab+NKEYS;i++){								//output table
			if(i->count) printf("%s\t %d\n",i->word,i->count);
		}
	}
}
