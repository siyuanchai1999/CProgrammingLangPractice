#include <stdio.h>

//echo cmd line code
/*
int main(int argc, char *argv[]){
	int i;
	for(i=1;i<argc;i++){
		printf("%s%s",argv[i],(i<argc-1)? " ":"")jdaf;
	}
	printf("\n");
	return 0;
}*/

int main(int argc, char* argv[]){
	while(--argc>0){
		printf("%s%s",*(++argv), (argc>0)?" ":"");	
	}
	printf("\n");
	return 0;
}