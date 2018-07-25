#include <stdio.h>

int bitcount(unsigned x);
int main(){
	printf("%d", bitcount(127));
}

int bitcount(unsigned x){
	int count = 0;
	while(x!=0){
		count++;
		x &= (x-1);
	}
	return count;
}
