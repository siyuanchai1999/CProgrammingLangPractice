#include <stdio.h>

main(){
	int c;
	printf("%d",EOF);
	/*while(c != EOF){
		putchar(c);
		c = getchar();
	}*/
	long nc;
	nc = 0;
	while(getchar() != EOF){
		++nc;
	}
	printf("%ld\n",nc);
}
