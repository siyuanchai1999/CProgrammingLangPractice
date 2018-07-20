#include <stdio.h>
#include <stdlib.h>


void roughcalc(){
	double sum = 0, v;
	int r;
	
	while((r = scanf("%lf",&v))== 1){
		printf("r = %d \t %.2f\n",r,
		sum += v);
	}
	printf("r = %d\n",r);
}

void literalChar(){
	int day, month, year;
	printf("format: year/month/day\n");
	scanf("%d/%d/%d",&year,&month,&day);
	printf("year: %d \nmonth = %d \nday = %d\n",year,month,day);
}

int main(){
	int p,q = 0,m = 0;
	scanf("%d:%d",&p,&q);
	printf("p = %d\n q = %d\nm = %d\n",p,q,m);
	return 0;
}
