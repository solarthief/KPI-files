#include "methods.h"



double* defineA(double a, double b, int n)
{
	double* A = new double[n];
	double h = (b - a) / n;
	for (int i = 0; i < n; ++i)
	{
		A[i] = func(a + (i + 1)*h);
	}
	return A;
}


double* defineC(double* A, double a, double b, int n)
{
	double* C = new double[n];
	double* res = gauss_elemination(defineSMatrix(A, a, b, n), n);
	for (int i = 0; i < n - 1; ++i)
		C[i] = res[i];
	C[n - 1] = 0;
	return C;
}


double* defineD(double* C, double a, double b, int n)
{
	double h = (b - a) / n;
	double* D = new double[n];
	for (int i = n - 1; i > 0; --i)
	{
		D[i] = (C[i] - C[i - 1]) / h;
	}
	D[0] = C[0];
	return D;
}

double* defineB(double* A, double* C, double* D, double a, double b, int n)
{
	double* B = new double[n];
	double h = (b - a) / n;
	B[0] = h*C[0] / 2 - h*h*D[0] / 6 + (A[0] - func(a)) / h;
	for (int i = 1; i < n; ++i)
		B[i] = h*C[i] / 2 - h*h*D[i] / 6 + (A[i] - A[i - 1]) / h;
	return B;
}


double** defineSMatrix(double* A, double a, double b, int n)
{
	double** M = new double*[n - 1];
	double h = (b - a) / n;
	for (int i = 0; i < n - 1; i++)
	{
		M[i] = new double[n];
		for (int j = 0; j < n; j++)
		{
			if (i == j) M[i][j] = 4 * h;
			else if ((j == i - 1) || (j == i + 1)) M[i][j] = h;
			else M[i][j] = 0;
		}
		double k = A[i + 1];
		if (i == 0)
			M[i][n - 1] = (6 / n)*(A[i + 1] - 2 * (A[i] - func(a)));
		else
			M[i][n - 1] = (6 / n)*(A[i + 1] - 2 * A[i] - A[i - 1]);
	}
	return M;
}


double* gauss_elemination(double** AM, int n)
{
	int i, j, k;
	double p, s;
	double* x = new double[n - 1];
	for (k = 0; k<n - 2; k++)
	{
		for (i = k + 1; i<n - 1; i++)
		{
			p = AM[i][k] / AM[k][k];
			for (j = k; j<n; j++)
				AM[i][j] = AM[i][j] - p*AM[k][j];
		}
	}
	x[n - 2] = AM[n - 2][n - 1] / AM[n - 2][n - 2];
	for (i = n - 3; i >= 0; i--)
	{
		s = 0;
		for (j = i + 1; j<n - 1; j++)
		{
			s += (AM[i][j] * x[j]);
			x[i] = (AM[i][n - 1] - s) / AM[i][i];
		}
	}
	return x;
}



double getInt(double x, double a, double b, int n, double*A, double*B, double*C, double*D)
{
	double xi = a, h = (b - a) / n;
	int i;
	for (i = 0; i < n; i++)
	{
		xi += h;
		if (x < xi) break;
	}
	double dx = (x - xi);
	return A[i] + B[i] * dx + C[i] * dx*dx / 2 + D[i] * dx*dx*dx / 6;
}