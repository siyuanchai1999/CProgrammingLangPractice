#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>

#define BUFFERSIZE 50

struct parameter{
	unsigned left;
	unsigned width;
	unsigned precision;
	unsigned preupdated;
}para ={0,0,0,0
};


int int2str(int i,char *s,int lim){
	int neg = 0, len = 0;
	if(i< 0){
		neg = -1;
		i = i*(-1);
	}
	if(i == 0){
		*s++ = '0';
		len = 1;
	}
	while(--lim> 0 && i>0){
		*s++ = i%10 + '0';
		i /= 10;
		len++;
	}
	if(neg == -1){
		*s++ = '-';
		len++;
	} 
	*s = '\0';		//str is in reverse order
	return len;
}

int strcatMult(char *dest, int pos, char c, int num){
	while(num-- > 0 ){
		*(dest + (pos++)) = c;
	}
	*(dest + pos) = '\0';
	return pos;
}

int strInsSpace(char *dest, int num, int len){
	char *temp = (char *) malloc(len);
	int ultimateLen = 0;
	strcpy(temp,dest);
	char *tp = temp;
	while(num-- > 0){
		*dest++ = ' ';
		ultimateLen++;
	}
	while(len-- > 0 ){
		*dest++ = *temp++;
		ultimateLen++;
	}
	*dest = '\0';	
	free(tp);
	return ultimateLen;
}
/*
left	  = align left or not
width     = minimum field width
precision = minimum of digits for integer
*/
void showStrRev(char *s, int len);
int intPrintFix(char *p,int len){
	int neg = 0;
	if(*(p + len - 1) == '-'){
		neg = -1;
		len = len -1;
	}
	len = strcatMult(p,len,'0',para.precision - len);
	if(neg == -1){
		*(p + (len++)) = '-';
		*(p + len) = '\0';
	}
	if(!para.left){
		len = strcatMult(p,len,' ',para.width - len);
	}else{
		len = strInsSpace(p,para.width - len,len);
	}
	return len;
}


void showStrRev(char *s, int len){
	while(--len>= 0){
		putchar(*(s+len));
	}
}
/** auto processing negative num parameter**/
int insertHeadChar(char *str,char toInsert,int num, int len){
	int finalLen = len + (num>0 ? num : 0);
	while(--len >= 0 && num> 0){
		*(str+len+num) = *(str+len);
	}
	
	*(str+finalLen) = '\0';
	
	while(--num >= 0){
		*(str+num) = toInsert;
	}
	return finalLen;
}

int strMoveLeft(char *str,int num,int len){
	if(num < 0){
		len = 0;
		num = num *(-1);
		while((*str = *(str+num)) != '\0'){
			str++;
			len++;
		}
		return len;
	}else{
		return len;
	}
}


int doublestrFix(char *str,int dotPos,int len){
	char *temp = (char *) malloc(dotPos + 1);
	int i = 0;
	while(i < dotPos){					//copy int portion to temp;
		*(temp + i) = *(str + i);
		i++;
	}
	*(temp + i) = '\0';
	
	len = strMoveLeft(str,(dotPos + 1)*(-1),len);
	i = 0;
	*(str + (len++)) = '.';

	while(i < dotPos){
		*(str + (len++)) = *(temp+ (i++));
	}
	*(str + len) = '\0';
	int start = 0, end = len - dotPos - 2;
	char tp;
	while(start<end){				//reverse the fract portion
		tp = *(str+start);
		*(str+start) = *(str+end);
		*(str+end) = tp;
		start++;
		end--;
	}
	return len;
}

int double2str(double dval,char *str,int lim){
	int ival = (int) dval;
	int len = int2str(ival,str,lim);
	int neg = 0,dotPos = 0;
	if(*(str+len-1) == '-'){
		neg = -1;
		len--;
	}
	if(ival != dval){
		*(str+(len)) = '.';
		dotPos = len++;
	}
	lim -= len;
	while(lim-- > 0 && dval != ival){
		ival = (int) ( dval = (dval - ival) * 10);
		*(str+(len++)) = ival%10 + '0';
	}
	*(str+len) = '\0';
	return doublestrFix(str,dotPos,len);
}



/*
width = field width complement
precision = number of digits after floating point
*/
 
int doubleFix(char *p,int len){
	int neg = 0,oldPre = 0;
	while(*(p+(oldPre)) != '.'){    //how many digits currently the num has
		oldPre++;
	}
	if(!para.preupdated) para.precision = 6; //default precision value
	
	//printf("left = %d \t width = %d \t precision = %d \t oldPre = %d\n",para.left,para.width,para.precision,oldPre);

	int movDist = para.precision - oldPre;
	len = (movDist > 0) ? insertHeadChar(p,'0',movDist,len) : strMoveLeft(p,movDist,len);
	
	len = (para.left)  ?  insertHeadChar(p,' ',para.width - len,len):strcatMult(p,len,' ',para.width - len);
	
	*(p+len) = '\0';
	return len;
}
/*
left = align left;
width = minimum field width
precision = max number of chars in str
*/
int strFix(char *str,int len){
	if(para.preupdated && para.precision <len){
		*(str + para.precision) = '\0';
		len = para.precision;
	}
	
	len = (!para.left) ? insertHeadChar(str,' ',para.width - len,len) : strcatMult(str,len,' ',para.width - len);
	*(str+len) = '\0';
	return len;
}


int hex2str(char *str,int ival,int lim){
	if(ival > 0 ){
		int len = 0;
		char append;
		while(ival > 0){
			append = ((ival%16 > 10) ? (ival%16 - 10) + 'A' : ival%16 + '0');
			*(str+(len++)) = append;
			ival /= 16;
		}
		*(str+len) = '\0';
		return len;
	}else if(ival == 0){
		*str++ = '0';
		*str = '\0';
		return 1;
	}else{
		return 0;
	}
}

int charPrintFix(char *str,int len){
	len = (para.left)  ?  insertHeadChar(str,' ',para.width - len,len):strcatMult(str,len,' ',para.width - len);
	return len;
}
char *findkey(char *p){
	while(isdigit(*p) || *p == '-' || *p == '.'|| isspace(*p))
		p++;
	return p;
}

void clearpara(){
	para.left = 0;
	para.precision = 0;
	para.width = 0;
	para.preupdated = 0;
}

void getinfo(char *start, char *end){
	//*start should = '%'
	//printf("start:%s \t end: %s\n",start,end);
	//printf("left = %d \t width = %d \t precision = %d\n",para.left,para.width,para.precision);
	int *given = &(para.width);
	if(*start == '-') para.left = 1;
	while(start < end){
		if(*start == '.'){
			given = &(para.precision);
			para.preupdated = 1;
		}
		if(isdigit(*start)) *given = (*given) *10 + (*start - '0');
		start++;
	}
}

void myprintf(char *fmt,...){
	va_list ap;
	char *p,*sval, *temp;
	char buffer[BUFFERSIZE];
	int ival;
	char cval;
	double dval;
		
	
	int len,index;
	
	va_start(ap, fmt);
	for(p = fmt; *p ; p++){
		if(*p != '%'){
			putchar(*p);
		}else{
			temp = ++p;
			p = findkey(p);
			getinfo(temp,p);
			switch(*p){
				case 'i':
				case 'd':
					ival = va_arg(ap,int);
					len = int2str(ival,buffer,BUFFERSIZE);
					len = intPrintFix(buffer,len);
					showStrRev(buffer,len);
					clearpara();
					break;
				case 'f':
					dval = va_arg(ap,double);
					len = double2str(dval,buffer,BUFFERSIZE);
					len = doubleFix(buffer,len);
					showStrRev(buffer,len);
					clearpara();
					break;
				case 'x':
					ival = va_arg(ap,int);
					len = hex2str(buffer,ival,BUFFERSIZE);
					len = intPrintFix(buffer,len);
					showStrRev(buffer,len);
					clearpara();
					break;
				case 'c':
					cval = va_arg(ap,int);
					*buffer = cval;
					*(buffer+1) = '\0';
					len = charPrintFix(buffer,1);
					showStrRev(buffer,len);
					clearpara();
					break;
				case 's':
					index = 0;
					for(sval = va_arg(ap,char *); *sval; sval++){
						*(buffer + (index++)) = *sval; 
					}
					
					*(buffer+index) = '\0';
					index = strFix(buffer,index);
					char *ptr = buffer;
					while(*ptr){
						putchar(*ptr++);
					}
					clearpara();
					break;
				default:
					putchar(*p);
					break;
			}
		}
	}
	va_end(ap);
}

void testmyPrintfstr(){
	myprintf("testmyPrintfstr: ----\n");
	char s[15] = "hello, world";
	myprintf(":%s:\n",s);
	myprintf(":%10s:\n",s);
	myprintf(":%.10s:\n",s);
	myprintf(":%-10s:\n",s);
	myprintf(":%.15s:\n",s);
	myprintf(":%-15s:\n",s);
	myprintf(":%15.10s:\n",s);
	myprintf(":%-15.10s:\n",s);
	myprintf("test done\n\n");
}

void testmyPrintfchar(){
	char c = 'p';
	myprintf("testmyPrintfchar: ----\n");
	myprintf(":%c:\t",c);
	printf(":%c:\n",c);
	
	myprintf(":%10c:\t",c);
	printf(":%10c:\n",c);
	
	myprintf(":%.10c:\t",c);
	printf(":%.10c:\n",c);
	
	myprintf(":%-10c:\t",c);
	printf(":%-10c:\n",c);
	
	myprintf("test done\n\n");
}

void testprintdouble(){
	myprintf("testprintdouble: ----\n");
	double x =211.9856789;
	myprintf(":%f:\t",x);
	printf(":%f:\n",x);
	
	myprintf(":%10f:\t",x);
	printf(":%10f:\n",x);
	
	myprintf(":%.10f:\t",x);
	printf(":%.10f:\n",x);
	
	myprintf(":%-10f:\t",x);
	printf(":%-10f:\n",x);
	
	myprintf(":%.15f:\t",x);
	printf(":%.15f:\n",x);

	myprintf(":%-15f:\t",x);
	printf(":%-15f:\n",x);
	
	myprintf(":%15.2f:\t",x);
	printf(":%15.2f:\n",x);
	
	myprintf(":%-15.2f:\t",x);
	printf(":%-15.2f:\n",x);
	myprintf("test done\n\n");
}

int main(){
	int i = -432,j = 0,k = -5;
	//myprintf("%-.4d%23.4d\n",32,-532);
	printf("%-8.5x\n",50);
	testmyPrintfchar();
	testmyPrintfstr();
	testprintdouble();
}
