#include <stdio.h> 

int binsearch(int x, int v[], int length);
int new_binsearch(int x, int v[], int length);
int main(){
	int v[] = {1,2,3,4,5,6,9};
	printf("%d",new_binsearch(9,v,7));
	
}
int binsearch(int x, int v[], int length){
	int low = 0;
	int high = length - 1;
	int mid;
	while(low<= high){
		mid = (low+high)/2;
		if(x>v[mid]){
			low = mid +1;
		}else if(x<v[mid]){
			high = mid - 1;
		}else{
			return mid;
		}
	}
	return -1;
}

int new_binsearch(int x, int v[], int length){
	int low = 0;
	int high = length - 1;
	int mid;
	while(low <= high){
		mid = (low + high)/2;
		if(x>v[mid]){
			low = mid + 1; 
		}else{
			high = mid - 1;
		}
	}
	if(v[mid] == x){
		return mid;
	}else{
		return -1;
	}
}

