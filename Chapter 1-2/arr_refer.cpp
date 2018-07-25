#include <stdio.h>

void arr_test(int *a);
int main(){
	int b[8] = {1,2,3,4,5,6,7,8};
	arr_test(b);
	/*for(int i = 0; i<8;i++){
		printf("%d\t", b[i]);
	}*/
}

void arr_test(int *a){
	printf("%d",a[0]);
}
