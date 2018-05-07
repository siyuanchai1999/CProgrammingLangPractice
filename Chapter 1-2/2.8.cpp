#include <stdio.h>

void squeeze(char s[], char c);
void strcat(char a[], char b[]);
int any(char s1[], char s2[]);
int any1(char s1[], char s2[]);
int main(){
	char st[10] = "123445";
	char stt[] = "345";
	char a[] = "445";
	//printf("%d\n", st[5]);
	//squeeze(st, '2');
	//strcat(st, stt);
	//printf("%s", st);
	printf("%d\n",any(st, stt));
	printf("%d\n",any(st, a));
}

/*delete all c in string s*/
void squeeze(char s[], char c){
	int i, j;
	for(i=j=0; s[i] != '\0'; i++){
		if(s[i] != c){
			s[j++] = s[i];   //first reach j then ++
		}
	}
	s[j] = '\0';
}

void strcat(char a[], char b[]){
	int i,j;
	j = 0;
	while(a[j] != '\0'){
		j++;
	}
	while(b[i] != '\0'){
		//printf("%c",b[i]);
		a[j++] = b[i++];
	}
}

int any(char s1[], char s2[]){
	int result = -1;
	int i,j = 0;
	int temp = 0;
	for(i = 0; s1[i]!= '\0';i++){
		if(s1[i] == s2[j]){
			printf("i: %d\n", i);
			result = i;
			temp = i;
			for(j=0; s2[j]!= '\0';j++){
				if(s2[j] != s1[temp++]){
					result = -1;
					//break;
				}
			}
			if(result != -1) return result;
			j = 0; 
		}
	}
	return result;	
}

