#ifndef OPERATOR_H_
#define OPERATOR_H_

#define OPARRSIZE 11
int checkOPLib(char op);
double add(double a, double b);
double substract(double Minuend, double Subtrahend);
double multiply(double a, double b);
double divide(double Dividend, double divisor);
double power(double base, double index);
double module(double higher, double lower);
double factorial(double fact);
double negate(double input);

typedef double (*funcptr)(double,double);
funcptr getFunc(int index);

#endif
