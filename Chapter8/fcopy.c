#include <stdio.h>

int main(int argc, char *argv[]){
	int c;
	if(argc == 3){
		FILE *fp1 = fopen(*++argv,"r");
		FILE *fp2 = fopen(*++argv,"a");
		if(fp1 != NULL && fp2 != NULL){
			while((c = getc(fp1)) != EOF){
				putc(c,fp2);
			}
		}else{
			printf("open err\n");
		}
	}
}
