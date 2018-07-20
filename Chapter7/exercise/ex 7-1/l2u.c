#include <stdio.h>
#include <ctype.h>

int main(int argc, char *argv[]){
	int u2l = 0,c;
	while(--argc> 0 && **(++argv) == '-'){
		while(c = *++argv[0]){
			switch(c){
				case'u':
					u2l = 0;
					break;
				case 'l':
					u2l = 1;
					break;
				default:
					printf("Usage: l2u [-l][-u]\n");
					printf("default to upper\n");
					printf("-l\t upper to lower\n");
					printf("-u\t lower to upper\n");
					break;
			}
		}
	}
	
	//printf("u2l = %d\n",u2l);
	int (*f)(int) = u2l ? tolower : toupper;
	while((c = getchar()) != EOF){
		putchar((*f)(c));
	}
	return 0;
	
} 
