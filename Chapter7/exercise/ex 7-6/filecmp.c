#include <stdio.h>
#include <stdlib.h>
#define BUFFERS 1000


char *fgetline(char *str, int max, FILE *ip){
	int c;
	char *s = str;
	
	while(--max > 0 && (c = getc(ip)) != EOF){
		if( c == '\n'){
			break;
		}else{
			*s++ = c;
		}
	}
	*s = '\0';
	return (c == EOF && s == str) ? NULL : str;  		//all characters has been read
}

int strcmp(char *str1, char *str2){
	while(*str1 != '\0'&& *str2 != '\0' && (*str1 == *str2)){
		//printf("%d %c \t\t %d %c\n",*str1,*str1,*str2,*str2);
		str1++;
		str2++;
		
	}
	//printf("%d %c \t\t %d %c\n",*str1,*str1,*str2,*str2);
	return *str1 - *str2;
}

int main(int argc, char *argv[]){
	char *f1line = (char *) malloc(BUFFERS);
	char *f2line = (char *) malloc(BUFFERS);
	char *filename[argc];
	int i = 1;
	
	if(argc == 3){
		FILE *f1ptr = fopen(argv[1],"r");
		FILE *f2ptr = fopen(argv[2],"r");
		
		if(f1ptr == NULL || f2ptr == NULL){
			if(f1ptr == NULL) fprintf(stderr,"%s: can't open %s\n",argv[0],argv[1]);
			if(f2ptr == NULL) fprintf(stderr,"%s: can't open %s\n",argv[0],argv[2]);
			exit(1);
		}else {
			i = 1;
			
			while((f1line = fgetline(f1line,BUFFERS,f1ptr)) != NULL && (f2line = fgetline(f2line,BUFFERS,f2ptr) )!= NULL){
				if(strcmp(f1line, f2line) != 0){
					break;
				}
				i++;
			}
			
			if(f1line == NULL) f2line = fgetline(f2line,BUFFERS,f2ptr);
			
			if(f1line == NULL && f2line == NULL){
				printf("%s and %s are same\n",argv[1],argv[2]);
			}else if(f1line == NULL){
				printf("%s ends at line %d\n",argv[1],i);
				printf("%s at line %d: %s\n",argv[2],i,f2line);
			}else if(f2line == NULL){
				printf("%s at line %d: %s\n",argv[1],i,f1line);
				printf("%s ends at line %d\n",argv[2],i);
			}else{
				printf("%s at line %d: %s\n",argv[1],i,f1line);
				printf("%s at line %d: %s\n",argv[2],i,f2line);
			}
			
		}	
		fclose(f1ptr);
		fclose(f2ptr);
	}else{
		printf("inappropriate arguments number\n");
		printf("usage: %s filename1 filename2\n",argv[0]);
	}
}
