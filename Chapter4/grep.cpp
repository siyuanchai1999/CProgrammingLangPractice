#include <stdio.h>
#include <string.h>
#define MAX 1000
/*get line into s[], return length*/
int getline(char s[], int lim){
	int c,i;
	i = 0;
	while(--lim>0 && (c=getchar())!= EOF && c !='\n'){
		s[i++] = c;
	}
	if(c == '\n') s[i++] = c;
	s[i] = '\0';
	return i;
}
/*get index of t within s, return -1 if not found*/
int stringindex(char s[], char t[]){
	int i,j,k=0;
	for(i=0;s[i]!='\0';i++){
			for(j=i, k=0;t[k]!='\0' && s[j]==t[k];j++, k++)
				;
			if(k>0 && t[k]=='\0'){
				return i;
			}
	}
	return -1;
}
/*store input[] into store[]*/
int getinto(char store[], char input[]){
	int i,j;
	for(i=0;store[i]!= '\0';i++){
		;
	}
	for(j=0;input[j]!= '\0';j++){
		store[i++] = input[j];
	}
}
void clear(char in[]){
	for(int i=0;in[i]!='\0';i++){
		in[i] = '\0';
	}
}
int main(){
	char line[MAX];
	char final[MAX];
	clear(final);
	int found = 0;
	char t[] = "chin";
	while(getline(line,MAX)>0){
		if(stringindex(line,t)>=0){
			//printf("%s",line);
			getinto(final,line);
			found++;
		}
	}
	printf("%s",final);
	printf("found: %d", found);
}
