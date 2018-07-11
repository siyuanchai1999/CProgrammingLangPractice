#include <stdio.h>
#define width 3
#define storageLen 30

 
void swapM(int m[][width], int a, int b){
	int i, j, k;
	i = m[a][0];
	j = m[a][1];
	k = m[a][2];
	m[a][0] = m[b][0];
	m[a][1] = m[b][1];
	m[a][2] = m[b][2];
	m[b][0] = i;
	m[b][1] = j;
	m[b][2] = k;
}

int partitionM(int m[][width], int start, int end){
	int pivot = m[end][0];
	int i = start - 1, j = start;
	for(j=start; j<end;j++){
		if(m[j][0]<pivot){
			swapM(m,++i,j);
		}
	}
	swapM(m,i+1,end);
	return i+1;
}

void quickSortM(int m[][width], int left, int right){
	if(left<right){
		int x = partitionM(m,left,right);
		quickSortM(m,left,x-1);
		quickSortM(m,x+1,right);
	}
}

void showMatrix(int m[10][width]){
	printf("matrix result:--------\n");
	int i = 0,j = 0;
	for(i = 0;i<10;i++){
		for(j =0;j<width;j++){
			printf("%d\t",m[i][j]);
		}
		printf("\n");
	}
}

void initMatrix(int matrix[10][width],int nlines){
	matrix[0][0] = 0;
	matrix[0][1] = 0;
	matrix[0][2] = 0;
	matrix[9][0] = nlines;
	matrix[0][1] = 0;
	matrix[0][2] = 0;
}

void getSortedMatrix(int conList[], int matrix[10][width]){
	int i;
	for(i = 10;i<storageLen;i++){
		matrix[i-9][0] = conList[i];
		matrix[i-9][1] = (i%2 == 0)? 0:1;
		matrix[i-9][2] = (i-10)/2;
	}
	quickSortM(matrix,1,8);
}

