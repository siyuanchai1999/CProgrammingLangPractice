
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <ctype.h>

#define PERMS 0666 /* RW for owner, group, and others*/
#define BUFSIZE 1000

/*
 * long lseek(int fd, long offset, int origin)
 * offset relative to origin position
 * origin : 0 	beginning
 * 	    1	current pos
 * 	    2	ending
 *
 */



	
//function usage: insert  file2 after line l of file1
//insert file1 [num] file2
//append file2 at the end of file1 if num not declared


int inc(int offset){
	return ++offset;
}

int dec(int offset){
	return --offset;
}


int checkNum(char *p, int *err){
	int neg = 1,result = 0;
	*err = 0;
	if(*p == '-'){
		neg = -1;
		p++;
	}
	while(isdigit(*p)){
		result = result * 10 + *p - '0';
		p++;
	}
	if(*p != '\0')	*err = 1;
	return result * neg;
}

int tryfind(int fd, int num, int *charnum){
	lseek(fd,0,0); //always start from the head
	char c;
	int curline=0;
	*charnum =0;
	while(curline != num  && read(fd,&c,1) > 0){
		(*charnum)++;
		/* \n takes read two times to read from the file handle??*/
		if(c == '\n'){
			curline++;
			(*charnum)++;
		}
	}
	
	//(*charnum)++;
	return curline;
}

int main(int argc, char *argv[]){
	int n, num = -1;
	int f1, f2;
	char c;
	int err;
	char buf[BUFSIZE];
	char *bufptr = buf;

	if(argc != 4 && argc != 3){
		fprintf(stderr,"lseek file1 [num] file2\n");
		exit(1);
	}else{
		if((f1 = open(argv[1],O_RDWR,0)) == -1){
			fprintf(stderr,"%s cannot be opened\n",argv[1]);
			exit(2);
		}
		num = checkNum(argv[2],&err);
		//printf("err = %d\n",err);
		if(err && argc == 3){
			num = -1;
			//printf("argv[2] = %s\n",argv[2]);
			if((f2 = open(argv[2],O_RDWR,0)) == -1){
				fprintf(stderr,"%s cannot be opened\n",argv[1]);
				exit(2);
			}
		}else if(err && argc == 4){
			fprintf(stderr,"error line number input: %s",argv[2]);
			exit(3);
		}else if(!err && argc == 3){
			fprintf(stderr,"need one more file");
			exit(4);
		}else if(!err && argc == 4){	
			if((f2 = open(argv[3],O_RDWR,0)) == -1){
				fprintf(stderr,"%s cannot be opened\n",argv[3]);
				exit(2);
			}
		}
		
		
		int linenum, charnum = 0;
		linenum = tryfind(f1,num, &charnum);
		if(num < 0 && linenum != num){
			num = linenum + num +1;
			num = (num < 0) ? 0 : num;
			linenum = tryfind(f1,num,&charnum);
		}
			
		while(bufptr - buf < BUFSIZE && read(f1,&c,1) > 0){
			*bufptr++ = c;
		}
		
		lseek(f1,charnum,0);
		while(read(f2,&c,1) > 0){
			if(write(f1,&c,1) != 1) fprintf(stderr,"writing %d %c to %s failed\n",c,c,argv[1]);
		}
		write(f1,buf,bufptr - buf);
		
		//for debugging purpose
	}

}	
