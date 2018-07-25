#include <stdio.h>
#define MAXLEN 1000

int getline(char s[], int lim);
void copy_arr(char to[], char from[]);
void print_arr(char arr[]);

int main(){
	int len;
	int max;
	char line[MAXLEN];
	char longest[MAXLEN];
	len = getline(line, MAXLEN);
	while(len>1){
		printf("there");
		if(len>max){
			max = len;
			printf("here");
			copy_arr(longest, line);
		}
		len = getline(line, MAXLEN);
	}
	if(max>0){
		print_arr(longest);
	}
}

int getline(char s[], int lim){
	int c, i;
	for(i=0;i<lim-1 && (c = getchar()) != EOF && c != '\n'; i++){
		s[i] = c;
	}
	if(c == '\n'){
		s[i] = '\n';
		i++;
	}
	s[i] = '\0';
	printf("%d",i);
	return i;
}

void copy_arr(char to[], char from[]){
	int i;
	i = 0;
	
	while((to[i] = from[i]) != '\0'){
		i = i+1;
	}
}
void print_arr(char arr[]){
	int i;
	i = 0;
	while(arr[i] != '\0'){
		printf("%s", arr[i]);
		i = i+1;
	}
}
