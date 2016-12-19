#include "sinx.h"
#include <iostream>

Sin::Sin() {}
Sin::~Sin() {}

double Sin::cast(double x) 
{
	const double d_pi = 2*M_PI;
	sign = 1;
	f = SIN;
	
	if(x > 0) 
		while(x >= d_pi) x -= d_pi;
	else
	{
		while (x <= d_pi) x += d_pi;
		if (x >= d_pi) x -= d_pi;
	};
	if (x >= M_PI)
	{
		sign = -1;
		x -= M_PI;
	};
	if (x >= M_PI_2) x = M_PI - x;
	if (x >= M_PI_4)
	{
		f = COS;
		x = M_PI_2 - x;
	};
	return x;
}


Result Sin::AccuracyValue(double x, double eps) {
	double U, result = 0;
	int k;
	double lib_sin = sin(x);
	Result Res;
	
	x = cast(x);
	U = x;
	if (f == SIN) 
	{
		for(k = 1; abs(U) >= eps; ++k) 
		{
			result += U;
			U *= x*x/(2*k * (2*k + 1));
		}
	}
	else 
	{
		U = 1;
		for(k = 1; abs(U) >= eps; ++k) 
		{
			result += U;
			U *= x*x/(2*k * (2*k - 1));
		}
	}
	result *= sign;
	
	Res.absEr = abs(result - lib_sin);
	Res.n = k;
	Res.remT = U;
	Res.f_x = result;

	return Res;
}

Result Sin::AbsoluteError(double x, int n) {
	double U, result = 0;
	double lib_sin = sin(x);
	int k = 1;
	Result Res;

	Res.remT = 0;
	if(n > 0) 
	{
		x = cast(x);
		U = x;
		x *= x;
		if (f == SIN) 
		{
			while(--n) 
			{
				result += U;
				U *= x/(2*k * (2*k + 1));
				k++;
			}
		}
		else 
		{
			U = 1;
			while(--n) 
			{
				result += U;
				U *= x/(2*k * (2*k - 1));
				k++;
			}
		}
		result *= sign;
		Res.remT = U;
	}
	Res.absEr = abs(result - lib_sin);
	Res.n = k;
	Res.f_x = result;

	return Res;
}


