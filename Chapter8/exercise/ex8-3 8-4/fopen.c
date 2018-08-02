#define NULL	0
#define EOF	(-1)
#define BUFSIZ	8 
#define OPEN_MAX	20

typedef struct _iobuf{
	int cnt;
	char *ptr;
	char *base;
	int flag;
	int fd;
}FILE;

enum _flags{
	_READ = 01,
	_WRITE = 02,
	_UNBUF = 04,
	_EOF = 010,
	_ERR = 020
};

FILE _IOB[OPEN_MAX] = {
	{ 0, (char *) 0, (char *) 0,  _READ, 0},
	{ 0, (char *) 0, (char *) 0,  _WRITE, 1},
    { 0, (char *) 0, (char *) 0,  _READ | _WRITE | _UNBUF, 2}
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

#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#define PERMS 0666

FILE *FOPEN(char *name, char *mode){
	int fd;
	FILE *fp;
	
	if(*mode != 'r' && *mode != 'w' && *mode != 'a'){
		return NULL;
	}
	
	for(fp = _IOB; fp < _IOB + OPEN_MAX; fp++){
		if((fp->flag & (_READ | _WRITE)) == 0){		//find empty file
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
	fp->flag = (*mode == 'r') ? _READ : _WRITE;
	return fp; 

}

int _flushbuf(int x, FILE *fp){
	unsigned char c = x;
	char *bufst;
	int bufsize, numwriten;
	
	if((fp->flag & (_WRITE | _EOF | _ERR)) != _WRITE){
		return EOF;
	}
	if(fp->flag & _UNBUF){
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

int fflush(FILE *fp){
	if((fp->flag & (_WRITE | _EOF | _ERR)) != _WRITE){
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

	if((fp->flag & (_READ | _EOF | _ERR) ) != _READ){
	    return EOF;
    }
    
	bufsize = (fp->flag & _UNBUF) ? 1 : BUFSIZ;
	
	if(fp->base == NULL){						//not buffered
		if((fp->base = (char *) malloc(bufsize)) == NULL){
			return EOF;					//malloc failure
		}
	}

	fp->ptr = fp->base;
	fp->cnt = read(fp->fd,fp->base,bufsize);

	if(--fp->cnt < 0){
		if(fp->cnt == -1){				//fp->cnt originally = 0, nothing was read
			fp->flag |= _EOF;
		}else{							//
			fp->flag |= _ERR;
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
		fp->flag = 0;
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
			if((fp->flag & _UNBUF) == 0 && (fp->flag & _WRITE) == _WRITE){
				fflush(fp);
				if(lseek(fp->fd,offset,origin) != -1) return 0;	
			} 
			if((fp->flag & _UNBUF) == 0 &&  (fp->flag & _READ) ==  _READ){
				int result = lseek(fp->fd,offset - fp->cnt,origin);
				fp->cnt =  read(fp->fd,fp->ptr,fp->cnt);
				if(fp->cnt != EOF) return 0;
			}
			return lseek(fp->fd,offset,origin) == EOF ? EOF : 0;	
		}
	}
	return EOF;
}

int main(int argc, char *argv[]){
	FILE *fp1 = FOPEN(*++argv,"r");
	FILE *fp2 = FOPEN(*++argv,"a");
	char c;
	
	while((c = getc(fp1)) != EOF){
		if(c == '\n') FSEEK(fp1,4L,0);
		putc(c, stdout);
	}
	
	fflush(stdout);
 
	return 0;

}
