#include <stdio.h>
#include <dirent.h>
#include <sys/types.h>
#define DIRSIZ 14
struct direct{
        ino_t d_ino;
        char d_name[DIRSIZ];
};

int main(){

	DIR *DIRPTR;
	struct dirent *direntptr;

	DIRPTR = opendir(".");
	while(DIRPTR != NULL && (direntptr = readdir(DIRPTR)) != NULL){
		printf("%s\n",direntptr->d_name);
	}
	
	//printf("fd = %d\n",fd);
	//struct direct dir;
	//printf("readin = %ld\n",read(fd,(char *) &dir, sizeof(dir)));
	//printf("dir.d_ino = %ld \t %s",dir.d_ino,dir.d_name);
}
