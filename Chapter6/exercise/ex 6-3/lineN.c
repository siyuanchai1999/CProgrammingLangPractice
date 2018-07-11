#include <stdio.h>
#include <string.h>

#include "getCharTest.c"

#define MAXWORDS 100
#define OCCUR 50
#define BUFFERSIZE 1000


char buffer[BUFFERSIZE];
char *bufferptr = buffer;
char *alloc(int len){
	if(bufferptr - buffer + len < BUFFERSIZE){
		bufferptr += len;
		return bufferptr - len;
	}else{
		printf("storage not enough");
		return NULL;
	}
}

void afree(char *p){
	if(p> buffer && p< buffer + BUFFERSIZE){
		bufferptr = p;
	}
}


struct word{
	char *string;
	int linenum[OCCUR];
	int ocurrence;
}wordlist[MAXWORDS];

int insertword(struct word wordlist[], char *w, int len, int lineN){
	int i, cond = 0;
	for(i = 0;i<len;i++){
		if(strcmp((wordlist[i]).string, w) == 0){
			wordlist[i].linenum[wordlist[i].ocurrence++] = lineN;
			cond = 1;
			break;
		}
	}
	if(cond == 0){
		//printf("w: %s\n",w);
		wordlist[len].string = alloc(strlen(w) + 1);
		strcpy(wordlist[len].string, w);
		wordlist[len].linenum[0] = lineN;
		wordlist[len++].ocurrence = 1;
		//printf("str: %s\n",wordlist[len-1].string);
	}
	return len;
}

void printwords(struct word wordlist[],int len){
	int i,j;
	for(i = 0; i<len; i++){
		printf("%s:",wordlist[i].string);
		for(j = 0; j<wordlist[i].ocurrence;j++){
			printf("  %d  ",wordlist[i].linenum[j]);
		}
		printf("\n");
	}
}

int checkNoise(char *word){
	if(strcmp(word,"and") == 0){
		return 0;
	}else if(strcmp(word,"the") == 0){
		return 0;
	}else if(strcmp(word,"a") == 0){
		return 0;
	}else if(strcmp(word,"an") == 0){
		return 0;
	}else if(strcmp(word,"like") == 0){
		return 0;
	}else{
		return 1;
	}
}
int getword(char *word, int lim){
	char *w = word;
	int c, cond = 1;
	while( (c = getch()) != '\n' && isspace(c) )
		;
	if(!isalpha(c)){
		*w = '\0';
		return c;
	}else{
		*w++ = c;
	}
	//printf("c: %d %c\n",c,c);
	while(--lim> 0 && cond){
		c = getch();
		if(isalnum(c)){
			*w++ = c;
		}else{
			//printf("returned c: %d %c\n",ungetch(c),c);
			ungetch(c);
			//printf("returned c: %d %c\n",c,c); 
			cond = 0;
		}
	}
	*w = '\0';
	return word[0];		
}

int main(){
	char word[MAXWORDS];
	int c, lineN = 1, len = 0;
	
	while((c = getword(word,MAXWORDS) )!= EOF){
		if(c == '\n'){
			//printf("line: %d\n",lineN);
			lineN++;
		}else if(isalpha(word[0])){
			//printf("word: %s ",word);
			if(checkNoise(word)){
				len = insertword(wordlist,word,len,lineN);		
			}
		}
	}
	//printf("%s\n",wordlist[1].string);
	printwords(wordlist,len);
}
