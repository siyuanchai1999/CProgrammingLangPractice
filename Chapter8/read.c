#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

#define BUFSIZE 100
int main(int argc, char *argv[]){
	char c;
	int n = open(*++argv,O_RDWR,0);
	lseek(n,12,0);
	while(read(n,&c,1)> 0){
		printf("c = %d %c\n",c,c);
	}
	return 0;
}
