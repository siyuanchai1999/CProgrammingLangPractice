#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include "getCharTest.c"


#define MAXTOKEN 1000
#define ALLOCSIZE 10000
enum {
	NAME,
	PARENS,
	BRACKETS
};
int tokentype;
char token[MAXTOKEN];
char out[MAXTOKEN*10];
char datatype[MAXTOKEN];
char name[MAXTOKEN];


char *lib[MAXTOKEN];
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

void initLib(){
	int i,libNum = 10;
	for(i = 0;i<libNum;i++){
		lib[i] = alloc(libNum);
	}
	strcpy(lib[1],"char");
	strcpy(lib[2],"double");
	strcpy(lib[3],"float");
	strcpy(lib[4],"int");
	
	strcpy(lib[5],"const");	
	//printf("init success!!\n");
}

int checkLib(char *p){
	int i,libNum = 10,result;
	//printf("p = %s\n",p);
	for(i = 1;i<libNum;i++){
		//printf("%s\n",lib[i]);
		result = strcmp(p,lib[i]);
		//printf("check %d item",i);
		if(result == 0) return i;
		
	}

	return 0;
}
	
int gettoken(void){
	int c;
	char *p = token;
	while((c = getch()) == ' ' ||  c == '\t' )
		;
	//printf("c:%d %c\n",c,c);
	if(c == '(' ){
		if((c = getch()) == ')'){
			strcpy(token,"()");
			return tokentype = PARENS;
		}else{
			ungetch(c);
			return tokentype = '(';
		}
	}else if(c == '['){
		*p++ = c;
		while((*p++ = getch()) != ']' )
			;
		*p = '\0';
		return tokentype = BRACKETS;
	}else if(isalpha(c)){
		*p++ = c;
		while(isalnum(c = getch()) ){		  //isalnum check the character is digit or letter
			*p++ = c;
		}
		*p = '\0';
		ungetch(c);
		//printf("token: %s\n",token);
		//printf("back to stream:%d %c\n",ungetch(c),c);
		return tokentype = NAME;
	}else{
		return tokentype = c;
	}
}

int ungettoken(char *to){
	int len = 0;
	while(*to != '\0'){
		len++;
		to++;
	}
	while(len-->0){
		ungetch(*(--to));
	}
	return 0;
}

int main(){
	initLib();
	int type;
	char temp[MAXTOKEN];
	while(gettoken() != EOF){
		if(tokentype == NAME){
			//printf("token: %s\t out:%s\t\n",token,out);	
			strcpy(out, token);
			while((type = gettoken()) != '\n' && type != EOF){
				if(type == PARENS || type == BRACKETS){
					strcat(out,token);
				}else if(type == '*'){
					if((type = gettoken()) == NAME && checkLib(token)){
						//printf("token: %s\t out:%s\t\n",token,out);
						sprintf(temp,"%s *%s",token,out);
					}else{
						ungettoken(token);
						sprintf(temp, "(*%s)",out);
					}
					strcpy(out,temp);
					//printf("out: %s\n",out);
				}else if(type == NAME){
					//printf("in NAME: token: %s\t out:%s\t\n",token,out);
					sprintf(temp,"%s %s",token,out);
					strcpy(out,temp);
				}else{
					printf("invalid input: %s",token);
					break;
				}
			}
			printf("%s\n",out);
		}else{
			printf("invalid name input: %s",token);
		}	
		
	}
}
