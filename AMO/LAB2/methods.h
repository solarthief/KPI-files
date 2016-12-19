#pragma once

#define _USE_MATH_DEFINES

#include <cmath>
#include "Result.h"

class Method 
{
private:
public:
	typedef double (*type_func)(double x);
	Method(void);
	~Method(void);

	Result Iteration(double m, double M, double x, double eps, double(*fx)(double x));
	Result Bisection(double a, double  b, double eps, double(*fx)(double x));
};