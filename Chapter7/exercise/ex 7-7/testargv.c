#include <stdio.h>

int main(int argc, char *argv[]){
	char *p = *argv++;
	char *q = *argv++;
	printf("%s",p);
	printf("%s",q);
}
