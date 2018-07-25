#include <stdio.h>

int main(){
	char str[100] = "hello";
	printf(":%-s:\n",str);		//- align with the left
	printf(":%10s:\n",str);		//width, 	controls the minimum spaces take
	printf(":%.3s:\n",str);		//precision, regulates the maximum output characters
	printf(":%.10s:\n",str);
	printf(":%10.3s:\n",str);
	printf("0x%x\n",15);	
}
