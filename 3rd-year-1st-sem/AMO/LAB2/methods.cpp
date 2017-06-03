#include "methods.h"

Method::Method(void) {};
Method::~Method(void) {};

Result Method::Iteration(double m, double M, double x, double eps, double(*fx)(double x)) 
{
	double x_n, lambda, q;
	int count = 0;
	Result resInf;

	lambda = 1/M;
	q = 1- m/M;

	do {
        x_n = x;
        x = x_n - lambda*fx(x_n);
		++count;
    } while(abs(x_n - x) > (1 - q)*eps/q);

	 resInf.x = x;
	 resInf.clarRoot = abs(x - x_n);
	 resInf.count = count;

	return resInf;
}

Result Method::Bisection(double a, double  b, double eps, double(*fx)(double x)) 
{
	

	double x, c;
	int count = 0;
	Result resInf;

	while(abs(b - a) >= 2*eps) {
		c = (a + b)/2;
		if((fx(a)*fx(c)) < 0)
			b = c;
		if((fx(b)*fx(c)) < 0)
			a = c;
		++count;
	}
	x = (a + b)/2;

	resInf.x = x;
	resInf.clarRoot = (b - a) * 0.5;
	resInf.count = count;
	return resInf;
}



