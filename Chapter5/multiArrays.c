#include <stdio.h>

static int daytab[2][13] = {
	{0,31,28,31,30,31,30,31,31,30,31,30,31},
	{0,31,29,31,30,31,30,31,31,30,31,30,31}
};

int day_of_year(int year, int month, int day){
	if(year<0){
		printf("invalid year input");
		return 0;
	}else if(month<=0 || month >12){
		printf("invalid month input");
		return 0;
	}else if(day <= 0 || day>31){
		printf("invalid day input");
		return 0;
	}else{
		int i, leap;
		leap = (year%4 == 0);
		for(i=1;i<month;i++){
			day = day + daytab[leap][i];
		}
	}
	return day;
}

void month_day(int year,int yearday, int *pmonth, int *pday){
	if(year<0){
		printf("invalid year input");
	}else if(yearday<0 || yearday>366){
		printf("invalid yearday input");
	}else{
		int i, leap;
		leap = year%4 == 0;
		for(i =1;yearday>0;i++){
			yearday -= daytab[leap][i];
		}
		*pmonth = i-1;
		*pday = yearday + daytab[leap][i-1];	
	}

}

int sumAll(int arr[][13]){
	int i,j=0,sum = 0;
	for(i = 0;i<2;i++){
		for(j=0;j<13;j++){
			sum += arr[i][j];
		}
	}
	return sum;
}

char *month_name(int n){
	static char *m_name[] = {
		"invalid month name",
		"January",
		"Feburary",
		"March",
		"April",
		"May",
		"June",
		"July",
		"August",
		"September",
		"October",
		"November",
		"December"
	};
	return (n<1 || n>13) ? m_name[0] :m_name[n];
}

int main(){
	printf("March 1: %d\n",day_of_year(2018,9,999));
	int month = 0, day = 0;
	month_day(2018,60,&month,&day);
	printf("2018-%d-%d\n",month, day);
	printf("days of 2019 and 2020: %d\n",sumAll(daytab));
	printf("%s\n",month_name(13));
	printf("%s\n",month_name(3));
}
