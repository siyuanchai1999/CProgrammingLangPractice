#include <stdio.h>
#include <string.h>

void printd(int n, char s[],int j){
	static int i;
	if(n<0){
		n = -n;
		s[i++] = '-';
	}
	if(n/10>0){
		
		printd(n/10,s,0);
	}
	s[i++] = (n%10) + '0';
	if(j){  //clear zero & return back
		while(s[i]!='\0'){
			s[i] = '\0';
			i++;
		}
		i = 0;
	} 
}

void swap(int v[], int i, int j){
	int temp = v[i];
	v[i] = v[j];
	v[j] = temp;
}
void print_arr(int x[]){
	int i;
	for(i=0;i<7;i++){
		printf("%d   ",x[i]);
	}
	printf("\n");
}

void qsort(int v[], int left, int right){
	int i, last;
	
	if(left>= right){
		return;
	}
	swap(v,left,(left+right)/2);
	last = left;
	for(i = left+1;i<= right;i++){
		if(v[i]<v[left]){
			swap(v,++last,i);
		}
	}
	swap(v,last,left);
	qsort(v,left, last-1);
	qsort(v,last+1,right);
}

void reverse(char s[],int length){
	int j = strlen(s);
	char temp = s[j-1];
	s[j-1] = '\0';
	if(s[0]!='\0'){
		reverse(s,length);
	}
	s[length - j] = temp;	
}


int main(){
	int i;
	int a = 33180;
	char s[100];
	printd(a,s,1);
	printf("s:%s\n",s);
	a = 555;
	printd(a,s,1);
	printf("s:%s\n",s);
	
	int b[] = {22,4,4,9,12,0,5,2};
	qsort(b,0,7);
	for(i=0; i<8;i++){
		printf("%d  ",b[i]);
	}
	
	char m[] = " dk2;";
	reverse(m,strlen(m));
	printf("%s",m);
}
