#include "mainfunc.h"


double I(double a, double b, int n, function<double(double)> f)
{
	double h;
	double sum = 0.0;
	int i;
	h = (b - a) / n;
	for (i = 1; i < n; ++i)
	{
		sum += f(a + i * h);
	}
	return h*(f(a) + f(b) + sum);
}

double integrate(double a, double b, double eps, function<double(double)> f)
{
	int n = (int)(1 / sqrt(eps));
	double In = I(a, b, n, f);
	double I2n = I(a, b, 2 * n, f);
	double Rn = fabs(In - I2n) / 3;
	while (Rn > eps)
	{
		n *= 2;
		In = I(a, b, n, f);
		I2n = I(a, b, 2 * n, f);
		Rn = fabs(In - I2n) / 3;
	}
	return I2n;
}

/*
double integrate(double a, double b, double eps, function<double(double)> f)
{
	int n = (int)(1 / sqrt(eps));
	double h;
	double In, I2n,Rn;
	double sum = 0.0;
	int i;
	double f0 = f(a), fn = f(b);
	h = (b - a) / n;
	for (i = 1; i < n; ++i)
	{
		sum += f(a + i * h);
	}
	In = h*(f0 + fn + sum);
	n *= 2;
	do
	{
		sum = 0.0;
		for (i = 1; i < n; ++i)
			sum += f(a + i * h);
		I2n = h*(f0 + fn + sum);
		Rn = fabs(In - I2n) / 3;
		In = I2n;
		n *= 2;
	} while (!((Rn < eps)||((Rn/fabs(I2n))<eps)));

	return I2n;


}*/