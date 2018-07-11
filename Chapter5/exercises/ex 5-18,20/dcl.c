#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "getCharTest.c"

 
#define intSize 1000
#define MAXTOKEN 100
#define ALLOCSIZE 10000

int libNum = 1000;
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
	int i,libNum = 10;
	//printf("p = %s\n",p);
	for(i = 1;i<libNum;i++){
		//printf("%s\n",lib[i]);
		if(strcmp(p,lib[i]) == 0) return i;
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
		while((*p++ = getch()) != ']' && *(p-1) != EOF && *(p-1) != '\n')
			;
		if(*(p-1) != ']'){
			printf("err: missing ]\n");
			return -1;
		}
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

int dirdcl(char *locName, char *locOut);
int dcl(char *locName,char *locOut){
	int ns,valid = 0;
	
	for(ns = 0;gettoken() == '*';){
		ns++;
	}
	valid = dirdcl(locName,locOut);
	while(ns-->0){
		strcat(locOut,"pointer to ");
	}
	return valid;
}

int dirdcl(char *locName, char *locOut){
	int type,libPos,ns,tokenResult;
	if(tokentype == '('){
		dcl(locName,locOut);
		if(tokentype != ')'){
			printf("err: missing )\n");
		}
	}else if(tokentype == NAME){
		strcpy(locName,token);
		//printf("copy token:%s to name:%s\n",token,name); 
	}else{
		printf("err: expected name or dcl\n");
	}
	
	while((type = gettoken()) == PARENS || type == BRACKETS){
		if(type == PARENS){
			strcat(locOut,"function with no parameter returning ");
		}else{
			strcat(locOut," array");
			strcat(locOut,token);
			strcat(locOut," of ");
		}
	}
	//printf("type: %d %c\t",type, type);
	if(type == '('){
		int paraNum = 0;
		strcat(locOut,"function with parameter of [");
		char *newOut = alloc(MAXTOKEN*10);
		char *dtype = alloc(MAXTOKEN);
		char *newName = alloc(MAXTOKEN);
		while((tokenResult = gettoken()) != ')' && tokenResult != '\n' && tokenResult != EOF){
			//printf("tokenResult= %d %c  token:%s\n",tokenResult,tokenResult,token);
			if(checkLib(token)){
				strcpy(dtype,token);	
			}else{
				printf("err: invalid datatype\n"); 
			}
			*newOut = '\0';
			dcl(newName,newOut); 
			if(tokentype != '\n' &&  tokentype != EOF && tokentype != ')' && tokentype != ','){
				printf("syntax err in function parameter\n");
				return 1;
			}else{
				if(paraNum) strcat(out, ", ");
				paraNum ++;
				strcat(out,newName);
				strcat(out,": ");
				strcat(out,newOut);
				strcat(out,dtype);
			}
		}
		strcat(out, "] returning ");
		afree(newName);
		afree(dtype);
		afree(newOut);
	}
	
}

int main(){
	initLib();
	while(gettoken() != EOF){
		if(checkLib(token)){
			strcpy(datatype,token);	
		}else {
			printf("err: invalid datatype");
			break;
		}
		//printf("tokentype:%d\n",tokentype==NAME);
		//printf("datatype:%s\n",token);
		*out = '\0';
		if(dcl(name,out)){
			
		}else if(tokentype != '\n' &&  tokentype != EOF){
			printf("syntax err\n");
		}else{
			printf("%s: %s %s\n",name,out,datatype);
		}
		
	}
}
