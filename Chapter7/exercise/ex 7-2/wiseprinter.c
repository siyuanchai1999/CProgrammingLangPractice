#include <stdio.h>
#include <string.h>
#include "getCharTest.c"
#define THRESHOLD 60
int getword(char *w, int lim){
	int c;
	while(--lim> 0 && (isalnum(c = getch()) || c == '.' || c == ',' || c == ';' ||c == '-')){
		*w++ = c;
	}
	*w = '\0';
	ungetch(c);
	return c;
	
}
int main(){
	char word[50];
	int charPerLine = 0,c;
	while((c = getch()) != EOF){
		if(isalnum(c)){
			word[0] = c;
			getword(&word[1],49);
			charPerLine += strlen(word);
			printf("%s",word);
			if(charPerLine>60){
				printf("\n");
				charPerLine = 0;
				if((c =getch()) != ' ') ungetch(c);
			}
			
		}else{
			if( c <127){
				printf("%c",c);	
			}else{
				printf("0x%x",c);
			}
			charPerLine++;
		}
		
	}
	
}
