#include "mainfunc.h"

double func(double x)
{
	return 10 * sin(x)*cos(x)*cos(11 * x);
}

double lejandr(int n, double x)
{
	double Pn1, Pn = x, Pn_1 = 1;
	if (n == 0) return Pn_1;
	int i = 1;
	while (i < n)
	{
		Pn1 = ((2 * n + 1) / (n + 1))*x*Pn - (n / (n + 1))*Pn_1;
		Pn_1 = Pn;
		Pn = Pn1;
		++i;
	}
	return Pn;
}

double* createconstA(double a, double b, double eps, int N, function<double(double)> f)
{
	double ** A = new double*[N + 1];
	int i, j;
	for (i = 0; i < N + 1; i++)
	{
		A[i] = new double[N + 2];
	}

	for (i = 0; i < N + 1; i++)
	{
		for (j = 0; j < N + 1; j++)
			A[i][j] = integrate(a, b, eps, [&](double x) {return lejandr(i, x) * lejandr(j, x); });
		A[i][N + 1] = integrate(a, b, eps, [&](double x) {return lejandr(i, x) * f(x); });
	}
	auto res = gaussian_elimination(A, N + 1);
	return res;
}

double val(double*A, double x, int N)
{
	double Pn1, Pn = x, Pn_1 = 1, sum;

	sum = Pn_1*A[0];
	if (N == 0) return sum;
	sum += Pn*A[1];
	int i = 1;
	while (i < N + 1)
	{
		Pn1 = ((2 * N + 1) / (N + 1))*x*Pn - (N / (N + 1))*Pn_1;
		Pn_1 = Pn;
		Pn = Pn1;
		sum += Pn*A[i + 1];
		++i;
	}
	return sum;
}

int main()
{
	ofstream tbl("table.csv");
	
	for (int n = 10; n < 100; n++)
	{
		
		double* A = createconstA( -1, 1, 0.0001, n, func);
		if (sqrt((integrate(-1, 1, 0.00001, [&](double x) {return (func(x) - val(A,x,n)) * (func(x) - val(A,x,n)); })) / 2) < 0.01)
		{
			for (double x = -1; x <= 1; x += 0.02)
			{
				cout << x << ";   " << val(A,x,n) << ";   "<<endl;
				tbl << x << ";" << val(A,x,n) << ";"<<endl;
			}
			break;
		}
	}
	
		return 0;
	
}
