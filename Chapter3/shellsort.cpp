#include <stdio.h> 

void print_arr(int v[], int length){
	for(int k=0;k<length;k++){
		printf("%d  ",v[k]);
	}
	printf("\n");
}

void shellsort(int v[], int length){
	int gap, i, j, temp;
	
	for(gap = length/2;gap>0;gap/=2){
		for(i = gap; i<length; i++){
			for(j = i-gap;j>=0 && v[j]>v[j+gap];j-=gap){
				temp = v[j];
				v[j] = v[j+gap];
				v[j+gap] = temp;
				//print_arr(v,length);
			}
			//printf("middle loop %d: ", i);
			//print_arr(v,length);
		}
	} 
}
void reverse(int v[], int length){
	int temp;
	for(int i=0;i<=length/2;i++){
		temp = v[i];
		v[i] = v[length -i-1];
		v[length -i-1] = temp;
	}
}

void expand(char s1[],char s2[]){
	char front, back, lastBack;
	int index = 0;
	for(int i=1;s1[i]!='\0';i++){
		if(s1[i]=='-'){
			front = s1[i-1];
			back = s1[i+1];
			int x = 0;
			if(lastBack == front) x = 1;
			while(front+x<=back){
				s2[index] = (char) (front + x);
				//printf("%c ",s2[index]);
				index++;
				x++;
			}
			lastBack = back;
		}
	}
}
int main(){
	int a[10] = {4,5,2,3,1,9,9,6,3,3};
	 
	shellsort(a,10);
	print_arr(a,10);
	reverse(a,10);
	print_arr(a,10);
	char b[] = "a-b-c";
	char c[1000];
	expand(b,c);
	for(int i=0;c[i]!=0;i++){
		printf("%c ",c[i]);
	}
}
