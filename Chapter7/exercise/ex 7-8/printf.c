#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILENUM 3

struct file{
	char *name;
	FILE *fptr;
};



static struct file *fArr[FILENUM];

struct file *newFile(FILE *fp, char *fname){
	struct file *f = (struct file *) malloc(sizeof(struct file));
	f->fptr = fp;
	f->name = (char *) malloc(strlen(fname) +1);
	strcpy(f->name, fname);
	return f;
}

void printfile(FILE *f){
	int c;
	while((c = getc(f)) != EOF){
		putc(c,stdout);
	}
}

int main(int argc, char *argv[]){
	int fnum = 0;
	FILE *fp;
	
	if(argc < 2){
		printf("at least one file name as argument\n");
		printf("Usage: printf filename ...\n");
	}

	while(--argc > 0 && **++argv){
		if((fp = fopen(*argv,"r")) != NULL){
			if(fnum > FILENUM - 1){
				argc++;
				argv--;
				printf("files not loaded due to size limit: ");
				break;	
			} 
			fArr[fnum++] = newFile(fp,*argv);	
		}else{
			printf("file %s does not exist\n",*argv);
		}
	}
	
	
	while(--argc > 0 && **++argv){
		printf("%s \t",*argv);
	}
	if(fnum > FILENUM -1) printf("\n");
	
	int i;
	for(i = 0; i<fnum; i++){
		printf("-----------------%s-----------------\n",fArr[i]->name);
		printfile(fArr[i]->fptr);
		printf("----------------------------------\n\n\n\n\n");
	}
	
	
} 
