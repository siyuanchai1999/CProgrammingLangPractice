#include <stdio.h>
#include <string.h>

#define MAXLINE 1000
int getline(char *s, int lim){
	int c,i;
	i = 0;
	while(--lim>0 && (c=getchar())!= EOF && c !='\n'){
		*s++ = c;
		i++;
	}
	if(c == '\n') s[i++] = c;
	*s = '\0'; //str terminator 
	return i;
}


int main(int argc, char*argv[]){
	char line[MAXLINE];
	int found = 0, except = 0, number = 0,c;
	long lineno = 0;
	printf("argc%d\n",argc);
	while(--argc >0 && (*++argv)[0] == '-'){
		while(c = *++argv[0]){
			switch(c){
				case 'x':
					except = 1;
					break;
				case 'n':
					number = 1;
					break;
				default:
					printf("illegal parameters %c\n",c);
					argc = 0;
					found = -1;
					break;
			}
		}
	}
	printf("argc:%d\n",argc);
	if(argc	 != 1){
		printf("Usage: find [-x] [-n] pattern\n");
	}else{
		while(getline(line,MAXLINE) >0 ){
			lineno++;
			if((strstr(line, argv[1]) != NULL) != except){
				if(number){
					printf("%ld:",lineno);
				}
				found++;
				printf("%s",line);
			}
		}
	}
	return found;
}
