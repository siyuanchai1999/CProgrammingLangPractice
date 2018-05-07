#include <stdio.h>

main(){
	float constant = 4.0/3.0;
	printf("%f\n", constant);
	printf("%100.2f\n", constant);
	printf("hello World\n");
	float f,c;
	int low, upper, step;
	
	int a;
	while((a = getchar())!= EOF){
		putchar(c);
	}
	low = 0;
	upper = 300;
	step = 10;
	
	f = float(low);
	printf("fahr  celecius\n");
	while(f<upper){
		c = 5.0*(f-32.0)/9.0;
		printf("%3.0f %6.1f\n", f, c);
		f = f + step;
	}
}
