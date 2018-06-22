#include <stdio.h>
#define ALLOCSIZE 1000

int strlen(char *c){
	int n = 0;
	while(*c != '\0'){
		c++;
		n++;
	}
	return n;
}

void print_arr(int *arr){
	int i;
	for(i=0;i<2 ;i++){
		printf("%d   ",*arr);
		arr++;
	}
	printf("\n");
}
static char allocbuf[ALLOCSIZE];
static char *allocp = allocbuf;
char *alloc(int n){
	if(allocbuf + ALLOCSIZE - allocp >=n ){
		allocp += n;
		return allocp - n;
	}else{
		return 0;
	}
}

void afree(char *p){
	if(p>=allocbuf && p<allocbuf+ALLOCSIZE){
		allocp = p;
	}
}
/** copy String t to String s**/
void strcpy(char *s, char *t){
	while(*s++ = *t++ )
		;
}

int strcmp(char *s, char *t){
	while(*s == *t){
		if(*s == '\0') return 0;
		s++;
		t++;
	}
	return *s -*t;
}
/**Exercise 5-3. Write a pointer version of the function strcat that we showed
in Chapter 2: strca t (s ,t) copies the string t to the end of s.**/
void strcat(char *s, char *t){
	while(*s!='\0'){
		s++;
	}
	while(*t!='\0'){
		*s = *t;
		s++;
		t++;
	}
	*s = '\0';
}

/**Exercise 5-4. Write the function strend (s ,t ), which returns 1 if the string
t occurs at the end of the string s, and zero otherwis**/
int strend(char *s, char *t){
	int t_len = 0;
	while(*s != '\0'){
		s++;
	}
	while(*t != '\0'){
		t++;
		t_len++;
	}
	while(t_len>0 && *s == *t){
		t_len--;
		s--;
		t--;
		if(*s != *t) return 0;
	}
	return 1;
}
int main(){
	char a[] = "jkl";
	char b[] = "mkb";
	char *c  = "abc";//read only declared in this way 
	printf("b:%c  c:%c\n",*(b+2),*(c+2));
	printf("b:%c  c:%c\n",*(b+3),*(c+3));
	strcpy(b, c);
	printf("b:%s  c:%s\n",b,c);
	printf("strcmp:%d\n",strcmp(b,c));
	strcat(a,b);
	printf("a:%s\n",a);
	printf("strend:%d",strend(a,b));
	
	
} 
