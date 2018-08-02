#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define BUFSIZE 10

void fileout(int filehd){
	char buf[BUFSIZE];
	int count;
	while( (count = read(filehd,buf,BUFSIZE)) > 0){
		if(write(1,buf,count) != count){
			fprintf(stderr,"output to stdout failed\n");
		}
	}

}

int main(int argc, char *argv[]){
	int bufsize = 10,n,len = 0;
	
	while(--argc > 0 && **++argv){
		if( (n = open(*argv,O_RDONLY,0)) != -1){
			fileout(n);
		}else{
			fprintf(stderr,"cannot open %s\n",*argv);
		}
	}
	return 0;
}
