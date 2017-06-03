#include "methods.h"
using namespace std;



double func(double x)
{
	return 10 * sin(x)*cos(x)*cos(11 * x);
}

void main()
{
	ofstream tbl("tbl.csv");
	double a = -1.0, b = 1.0, x;
	int n = 100;
	double* A = new double[n];
	double* B = new double[n];
	double* C = new double[n];
	double* D = new double[n];
	double h = (b - a) / n;
	A = defineA(a, b, n);
	C = defineC(A, a, b, n);
	D = defineD(C, a, b, n);
	B = defineB(A, C, D, a, b, n);

	for (int i = 0; i < n; ++i)
	{
		x = a + i*h;
		cout << "x= " << x << ";  " << "f(x)= " << func(x) << ";  " << "Evalsp= " << getInt(x, a, b, n, A, B, C, D) << ";" << endl;
		tbl << x << ";" << getInt(x, a, b, n, A, B, C, D) << ";" << endl;
	}


	return;
}