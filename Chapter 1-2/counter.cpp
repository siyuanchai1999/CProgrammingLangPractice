#include <stdio.h> 

#define IN 1
#define OUT 0

main(){
	int c, nl, nw, nc, state;
	
	nw = nc = nl = 0;
	
	state = OUT;
	/*while((c = getchar())!= EOF){
		++nc;
		if(c == '\n'){
			nl++;
		}
		if(c == ' ' || c == '\n' || c == '\t'){
			state = OUT;
		}else if (state == OUT){
			state = IN;
			nw++;
		}
	}
	printf("%d %d %d \n",nl,nw,nc);*/
	
	/*while((c = getchar()) != EOF){
		if(c == ' ' || c== '\n'|| c == '\t'){
			printf("\n");
		}else{
			putchar(c);
		}
		
	}*/
	int max = -1;
	int num_digit[10];  // count digit of each number
	for(int i=0;i<10;i++){
		num_digit[i] =0;
	}
	while((c = getchar())!= EOF){
		if(c>='0' && c<= '9'){
			num_digit[c -'0']++;
		}
	}
	
	for(int i=0;i<10;i++){
		if(num_digit[i]>max){
			max = num_digit[i];
		}
	}
	printf("%d\n", max);
	
	for(int j=0;j<max;j++){
		for(int m=0;m<10;m++){
			if((max-j)<=num_digit[m]){
				printf("* ");
			}else{
				printf("  ");
			}
		}
		printf("\n");
	}
	
	for(int k=0;k<10;k++){
		printf("%d ",k);
	}
	//printf("digit:");
	/*for(int i=0;i<10;i++){
		//printf("%d: %d\n",i, num_digit[i]);
		printf("%d: ",i);
		for(int j=0; j<num_digit[i];j++){
			printf("*");
		}
		printf("\n");
	}*/
	
}


