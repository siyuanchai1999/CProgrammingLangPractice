#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

//#define NULL	0
#define EOF	(-1)
#define BUFSIZ	8 
#define OPEN_MAX	20

typedef struct _iobuf{
	int cnt;
	char *ptr;
	char *base;
	struct flag *flagptr;
	int fd;
}FILE;

struct flag{
	unsigned _READ: 1;
	unsigned _WRITE: 1;
	unsigned _UNBUF: 1;
	unsigned _EOF: 1;
	unsigned _ERR: 1;
};

void clearflag(struct flag *flagptr){
	flagptr->_READ = 0;
	flagptr->_WRITE = 0;
	flagptr->_UNBUF = 0;
	flagptr->_EOF = 0;
	flagptr->_ERR = 0;
}

FILE _IOB[OPEN_MAX] = {
	{ 0, (char *) 0, (char *) 0,  &(struct flag){1,0,0,0,0}, 0},
	{ 0, (char *) 0, (char *) 0,   &(struct flag){0,1,0,0,0}, 1},
    { 0, (char *) 0, (char *) 0,  &(struct flag){1,1,0,0,0}, 2}
};

int filecnt = 3;


#define stdin (&_IOB[0])
#define stdout (&_IOB[1])
#define stderr (&_IOB[2])


int _fillbuf(FILE *);
int _flushbuf(int x, FILE *fp);

#define feof(p) 	( ( (p)->flag & _EOF) != 0)
#define ferror(p) 	( ( (p)->flag & _ERR) != 0)
#define fileno(p)	( (p)->fd)

#define getc(p) 	(--(p)->cnt >=0 ? (unsigned char) *(p)->ptr++ : _fillbuf(p))
#define putc(x,p)	(--(p)->cnt >= 0 ? *(p)->ptr++ = (x) : _flushbuf((x),p))

#define getchar()	getc(stdin)
#define putchar(x) 	putc(x,stdout)
#define PERMS 0666

FILE *FOPEN(char *name, char *mode){
	int fd;
	FILE *fp;
	
	if(*mode != 'r' && *mode != 'w' && *mode != 'a'){
		return NULL;
	}
	
	for(fp = _IOB; fp < _IOB + OPEN_MAX; fp++){
		if(fp->flagptr == NULL){
			break;
		}else if(fp->flagptr->_READ == 0 && fp->flagptr->_WRITE == 0){		//find empty file
			break;
		}
	}
	if(fp >= _IOB + OPEN_MAX){						//not available space to open
		return NULL;
	}

	if(*mode == 'w'){
		fd = creat(name,PERMS);
	}else if(*mode == 'a'){
		if((fd = open(name,O_WRONLY,0)) == -1){
			fd = creat(name,PERMS);
		}
		lseek(fd,0L, 2);				//goes to the end of the file
	//	putc('!',stdout);
	}else{
		fd = open(name,O_RDONLY,0);
	}
	
	if(fd == -1){
		return NULL;
	}

	fp->fd = fd;
	fp->cnt = 0;
	fp->base = NULL;
	if(fp->flagptr == NULL){
//		fp->flagptr = &(struct flag){0,0,0,0,0};
		fp->flagptr = (struct flag *) malloc(sizeof(struct flag));
		fp->flagptr->_EOF = 0;
		fp->flagptr->_ERR = 0;
		fp->flagptr->_UNBUF = 0;
	}
	fp->flagptr->_READ = (*mode == 'r');
	fp->flagptr->_WRITE = (*mode == 'a' || *mode == 'w');
	return fp; 
}

int showint(int x){
	if(x == 0){
		putc('0',stdout);
		return 0;
	}
	int temp = x;
	char *charbase = (char *) malloc(sizeof(12));
	char *charptr = charbase;
	if(x < 0){
		x *= (-1);
		putc('-',stdout);
	}
	while(x > 0){
		*charptr++ = (x%10) + '0';
		x = x/10;
	}
	while(charptr > charbase){
		putc(*--charptr,stdout);
	}
	free(charbase);
	return temp;
}

int _flushbuf(int x, FILE *fp){
	unsigned char c = x;
	char *bufst;
	int bufsize, numwriten;
	
	if(!fp->flagptr->_WRITE ||fp->flagptr->_EOF || fp->flagptr->_ERR){
		return EOF;
	}

	if(fp->flagptr->_UNBUF){
		bufsize = 1;
		numwriten = write(fp->fd, &c, bufsize);
		fp->cnt = 0;
	}else{
		if(fp->base == NULL){		//not yet allocated
			if((fp->base = (char *) malloc(BUFSIZ)) == NULL){
				return EOF;
			}else{
				fp->ptr = fp->base;
			}
		}
		*fp->ptr++ = c;
		bufsize = (int) (fp->ptr - fp->base);
		numwriten = write(fp->fd,fp->base,bufsize);
		fp->ptr = fp->base;
		fp->cnt  = BUFSIZ - 1;
	}
	
	if(bufsize != numwriten){
		return EOF;
	}
	return c;
	
}

void showflag(FILE *fp){
	putc('#',stdout);
	putc(fp->flagptr->_READ + '0',stdout);
	putc(fp->flagptr->_WRITE + '0',stdout);
	putc(fp->flagptr->_UNBUF + '0',stdout);
	putc(fp->flagptr->_EOF + '0',stdout);
	putc(fp->flagptr->_ERR + '0',stdout);
	putc('#',stdout);
	putc('\n',stdout);
	//fflush(stdout);	
}

int fflush(FILE *fp){
	if(!fp->flagptr->_WRITE ||fp->flagptr->_EOF || fp->flagptr->_ERR){
		return EOF;
	}	
	
	if(fp->base == NULL){		//not buffered
		return EOF;
	}
	int shouldwriten = (int)(fp->ptr - fp->base);
	if(shouldwriten != write(fp->fd,fp->base,shouldwriten)){
		return EOF;
	}
	return *(fp->base);
}

int _fillbuf(FILE *fp){
	int bufsize;

	if(!fp->flagptr->_READ || fp->flagptr->_EOF || fp->flagptr->_ERR){
		showflag(fp);
		return EOF;
	}	
    
	bufsize = (fp->flagptr->_UNBUF) ? 1 : BUFSIZ;
	
	if(fp->base == NULL){						//not buffered
		if((fp->base = (char *) malloc(bufsize)) == NULL){
			return EOF;					//malloc failure
		}
	}
	
	
	fp->ptr = fp->base;
	fp->cnt = read(fp->fd,fp->base,bufsize);

	if(--fp->cnt < 0){
		if(fp->cnt == -1){				//fp->cnt originally = 0, nothing was read
			fp->flagptr->_EOF = 1;
		}else{							//
			fp->flagptr->_ERR = 1;
		}
		fp->cnt = 0;
		return EOF;
	}

	return (unsigned char) *fp->ptr++;
}

int FCLOSE(FILE *fp){
	if(fp == NULL){
		return EOF;
	}else{
		free(fp->base);
		fp->ptr = NULL;
		clearflag(fp->flagptr);
		fp->fd = -1;
		fp->cnt = 0;
		return 0;
	}
}

void showstr(char *str, int cnt){
	while(cnt-- > 0 && *str){
		putc(*str++,stdout);
	}
}

int FSEEK(FILE *fp, long offset, int origin){
	char str[10] = "fseek\n";
	if(fp != NULL){	
		if(origin >= 0 && origin <= 2){
			if(!fp->flagptr->_UNBUF && fp->flagptr->_WRITE){
				fflush(fp);
				if(lseek(fp->fd,offset,origin) != -1) return 0;	
			} 
			if(!fp->flagptr->_UNBUF && fp->flagptr->_READ){
				int result = lseek(fp->fd,offset - fp->cnt,origin);
				fp->cnt =  read(fp->fd,fp->ptr,fp->cnt);
				if(fp->cnt != EOF) return 0;
			}
			return lseek(fp->fd,offset,origin) == EOF ? EOF : 0;	
		}
	}
	return EOF;
}
`
int main(int argc, char *argv[]){
	
	FILE *fp1 = FOPEN(*++argv,"r");
	FILE *fp2 = FOPEN(*++argv,"w");
	char c;
	
	while(fp1 != NULL && fp2 != NULL &&  (c = getc(fp1)) != EOF){
		putc(c, fp2);
	}
	fflush(fp2);
 	FCLOSE(fp1);
	FCLOSE(fp2);
	return 0;

}
/*
 * timing result of bit field implementation
 * copy 10000 entries to dest file
	real	0m8.107s
	user	0m0.162s
	sys	0m2.591s

 * timing result of odinary implementation
 * copy 10000 entries to dest file
	real	0m8.135s
	user	0m0.227s
	sys	0m2.530s
 approximately the same
*/
