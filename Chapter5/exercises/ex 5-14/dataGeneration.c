#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(){
	printf("ehere\n");
	FILE *f = fopen("data.txt","w");
	printf("here\n");
	srand(700);
	int i =0;
	printf("here\n");

	while(i<100){
		double a = (double)rand()/10*(i++);
		printf("%f\t",a);
		fprintf(f,"%f\n",a);
	}
	
	fclose(f);
}
