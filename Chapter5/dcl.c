#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "getCharTest.c"

 
#define intSize 1000
#define MAXTOKEN 100
#define ALLOCSIZE 1000

enum {
	NAME,
	PARENS,
	BRACKETS
};
int tokentype;				//type of last token	
char token[MAXTOKEN];		//last token type
char name[MAXTOKEN];		//identifier name
char datatype[MAXTOKEN];   //data type == char, int
char out[MAXTOKEN*10];			   //output string

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
	int i,len = 10;
	for(i = 0;i<len;i++){
		lib[i] = alloc(len);
	}
	strcpy(lib[1],"char");
	strcpy(lib[2],"double");
	strcpy(lib[3],"float");
	strcpy(lib[2],"int");	
	printf("init success!!\n");
}

int checkLib(char *p){
	int i,len = 10;
	printf("p = %s\n",p);
	for(i = 1;i<len;i++){
		printf("%s\n",lib[i]);
		if(strcmp(p,lib[i]) == 0) return i;
	}
	return 0;
}


int gettoken(void){
	int c;
	char *p = token;
	while((c = getch()) == ' ' ||  c == '\t')
		;
	//printf("c:%d\n",c);
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
		while((*p++ = getch()) != ']')
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
		return tokentype = NAME;
	}else{
		return tokentype = c;
	}
}

void dirdcl(void);
void dcl(void){
	int ns;
	
	for(ns = 0;gettoken() == '*';){
		ns++;
	}
	dirdcl();
	while(ns-->0){
		strcat(out,"pointer to");
	}
}

void dirdcl(void){
	int type;
	if(tokentype == '('){
		dcl();
		if(tokentype != ')'){
			printf("err: missing )\n");
		}
	}else if(tokentype == NAME){
		strcpy(name,token);
		//printf("copy token:%s to name:%s\n",token,name); 
	}else{
		printf("err: expected name or dcl\n");
	}
	
	while((type = gettoken()) == PARENS || type == BRACKETS){
		if(type == PARENS){
			strcat(out,"function with no parameter returning ");
		}else{
			strcat(out," array");
			strcat(out,token);
			strcat(out," of ");
		}
	}
	if(type == '('){
		int paraNum = 0;
		strcat(out,"function with parameter of ");
		while((type = gettoken()) != ')'){
			if(checkLib(token) && paraNum){
				strcat(out, ",");
				paraNum++;
			} 
			strcat(out,token);
			strcat(out," ");
		}
		strcat(out," returning ");
		type = gettoken();
	}
}

int main(){
	initLib();
	while(gettoken() != EOF){
		strcpy(datatype,token);
		//printf("tokentype:%d\n",tokentype==NAME);
		//printf("datatype:%s\n",token);
		*out = '\0';
		dcl();
		if(tokentype != '\n' &&  tokentype != EOF){
			printf("syntax err\n");
		}else{
			printf("%s: %s %s\n",name,out,datatype);
		}
		
	}
}
