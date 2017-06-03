#pragma once
#define _USE_MATH_DEFINES

#include <cmath>
#include "Result.h"

class Sin 
{
private:
	enum Func {	SIN, COS };
	int sign;
	Func f;
	double cast(double x);

public:
	Sin();
	~Sin();
	Result AccuracyValue(double x, double eps);
	Result AbsoluteError(double x, int n);
};

