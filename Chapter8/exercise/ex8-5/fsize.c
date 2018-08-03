#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
//#include <sys/dir.h>
#include <dirent.h>
#include <time.h>


/*
#define NAME_MAX 14

typedef struct{
	long ino;
	char name[NAME_MAX+1];
} Dirent;

typedef struct{
	int fd;
	Dirent d;
}DIR;

#ifndef DIRSIZ
#define DIRSIZ 14
#endif
struct direct{
	ino_t d_ino;
	char d_name[DIRSIZ];
};

DIR *opendir(char *dirname){
	int fd;
	struct stat stbuf;
	DIR *dp;
	
	if( (fd = open(dirname,O_RDONLY,0)) == -1
	 || fstat(fd,&stbuf) == -1
	 || (stbuf.st_mode & S_IFMT) != S_IFDIR
	 || (dp = (DIR *) malloc(sizeof(DIR))) == NULL)
		return NULL;
	dp->fd = fd;
	return dp;
}

void closedir(DIR *dp){
	if(dp != NULL){
		close(dp->fd);
		free(dp);
	}
}

Dirent *readdir(DIR *dp){
	struct direct dirbuf;  //local directory structure, specified for unix system
	static Dirent d;
	int c;
	while((c = read(dp->fd,(char *) &dirbuf, sizeof(dirbuf))) == sizeof(dirbuf)){
		if(dirbuf.d_ino == 0){
			continue;
		}
		d.ino = dirbuf.d_ino;
		strncpy(d.name, dirbuf.d_name, DIRSIZ);
		d.name[DIRSIZ] = '\0';
		return &d;
	}
	printf("dp->fd = %d \t c = %d \t siezof(dirbuf) = %ld\n",dp->fd,c,sizeof(dirbuf));
	return NULL;
}

*/

#define MAX_PATH 1024
/*linux no longer allow open/read/write system calls on directory
 *struct dirent, DIR data structures defined in dirent.h can well solve this problem
 *
 */

/* dirwalk: apply fcn to all files in dir */
void tabprint(int count){
	while(count--> 0){
		printf("\t");
	}
}

void dirwalk(char *dir, void (*fcn)(char *,int,int *),int count,int *info){
	char name[MAX_PATH];
	struct dirent *dp;
	DIR *dfd;

	if((dfd = opendir(dir)) == NULL){
		//printf("invalid dir %s\n",dir);
		fprintf(stderr,"dirwalk: cannot access %s\n",dir);
		return;
	}

	while((dp = readdir(dfd)) != NULL){
		if(strcmp(dp->d_name, ".") == 0 || strcmp(dp->d_name,"..") == 0) continue;		//skip self and parent directory
		if(strlen(dir) + strlen(dp->d_name) + 2 > sizeof(name)){
			fprintf(stderr,"dirwalk: name %s%s too long\n",dir,dp->d_name);
		}else{
			sprintf(name,"%s/%s",dir,dp->d_name);
		//	printf("name = %s\n",name);
			(*fcn)(name,count,info);
		}
	}
	//printf("dp == NULL %d\n",dp == NULL);
	closedir(dfd);

}
void fsize(char *name,int count,int *info){
	struct stat stbuf;

	if(stat(name,&stbuf) == -1){
		fprintf(stderr,"fsize: cannot access %s\n",name);
		return;
	}
       	if((stbuf.st_mode & S_IFMT) == S_IFDIR){
		tabprint(count);
		printf("     dir:%s\n",name);
		dirwalk(name,fsize,count+1,info);
	}
	tabprint(count);
	printf("%8ld ",*info++ ? (stbuf.st_size+512)/1024:stbuf.st_size);
	if(*info++){
		char *buf = (char *) malloc(80);
		strftime(buf,80,"%x-%X",localtime(&stbuf.st_atime));
		printf("%8s",buf);
		free(buf);
	}else if(*info){
		char *buf = (char *) malloc(80);
		strftime(buf,80,"%x-%X",localtime(&stbuf.st_mtime));
		printf("%8s",buf);
		free(buf);
	}
	printf("%s\n",name);	
}

/*
 * fsize [-k] [-a] [-m] [directories...]
 * -k show size in kib, default in bytes
 * -a show last accessed time
 * -m show last modified time
 */

#define DIRLIMIT 20
int main(int argc, char *argv[]){
	int kib = 0, access = 0, modified = 0,c;
	char *wordptr[DIRLIMIT];
	int info[3];

	while(--argc > 0 && **++argv == '-'){
		while(c = *++argv[0]){
			switch(c){
				case 'k':
					kib = 1;
					break;
				case 'a':
					access = 1;
					break;
				case 'm':
					modified = 1;
					break;
				default:
				        printf("fsize [-k] [-a] [-m] [directories]");
					break;
			}
		}
	}
	printf("argc = %d \t kib = %d \t access = %d \t modified = %d\n",argc,info[0] = kib, info[1] = access, info[2] = modified);

	if(argc == 0){
		fsize(".",0,info);
	}else{
		while(argc-- > 0){
			fsize(*argv++, 0, info);
		}
	}
/*
	if(argc == 1){
		fsize(".",0);
	}else{
		while(--argc > 0){
			fsize(*++argv,0);
		}
	}
*/
	return 0;
}

