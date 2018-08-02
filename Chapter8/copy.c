#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#define PERMS 0666 /* RW for owner, group, and others*/
#define BUFSIZE 10

int main(int argc, char *argv[]){
	int f1, f2, n;
	char buf[BUFSIZE];

	if(argc != 3){
		fprintf(stderr,"two files needed as argument\ncopy from to\n");
		exit(1);
	}

	if((f1 = open(argv[1],O_RDONLY,0)) == -1){
		fprintf(stderr,"%s cannot be opened\n",argv[1]);
		exit(2);
	}

	if((f2 = creat(argv[2],PERMS)) == -1){
                fprintf(stderr,"cannot create file %s under mode %03o",argv[2],PERMS);
        	exit(2);
	}
	
	printf("f1 = %d \t f2 = %d\n",f1,f2);
	while((n = read(f1,buf,BUFSIZE)) > 0){
		printf("%s in buffer\n",buf);
		if(write(f2,buf,n) != n){
			fprintf(stderr,"failure when writing to %s\n",argv[2]);
		}
	}
	return 0;
}	
