#include <stdio.h>


union tag{
	int ival;
	float fval;
	char *sval;
};

int main(){
	char m[6] = "while";
	union tag u = { .fval = 4.4
	};
	u.ival = 3;
	printf("%f",u.fval);
};
