#include <math.h>
#include <stdio.h>

double func(double x) 
{
	return pow((3*x+1),5);
}

double funcFour(double x) 
{
	return 9720*(3*x+1);
}

double funcPerv(double x) 
{
	return pow((3 * x + 1), 6)/18;
}

double Integrate_Simpson(double n, double a, double b) 
{
	int i;
	double h;
	double sig1 = 0.0;
	double sig2 = 0.0;

	n = 2*ceil(n/2);
	h = (b - a)/n;
	for (i = 1; i < n; i++) 
	{
		if (i%2 == 0)
			sig2 += func(a + i*h);
		else
			sig1 += func(a + i*h);
	}
	return h/3*(func(a) + func(b) + 4*sig1 + 2*sig2);
}

int main() 
{
	int i, n;
	double a = 2.0;
	double b = 8.0;
	double e = 0.01;
	double r, h, max;
	double Io, In, I2n;
	double x, delta;

	Io = funcPerv(b) - funcPerv(a);
	printf("[a, b] = [%.1f, %.1f]\n", a, b);
	printf("I = F(b) - F(a) = %f\n\n", Io);

	printf("======================================================\n");
	printf("|     e    |   h   |      I            |    delta    |\n");
	printf("======================================================\n");
	x = a;
	max = funcFour(x);
	while (x < b) 
	{
		if (funcFour(x) > max) max = funcFour(x);
		x += e;
	}
	h = pow(180*e/(b - a)/max, 0.25);
	n = 2*ceil(0.5*(b - a)/h);
	h = (b - a)/n;
	delta = fabs(Io - Integrate_Simpson(n, a, b));
	printf("| %f | %.3f | %.8f | %.9f |\n", e, h, Integrate_Simpson(n, a, b), delta);
	printf("======================================================\n");

	printf("=====================================\n");
	printf("|    delta    |   h   |     Abs     |\n");
	printf("=====================================\n");
	n = ceil(1/pow(e, 0.25));
	In = Integrate_Simpson(n, a, b);
	I2n = Integrate_Simpson(2*n, a, b);
	r = fabs(In - I2n)/3;
	while (r > delta) 
	{
		n *= 2;
		In = Integrate_Simpson(n, a, b);
		I2n = Integrate_Simpson(2*n, a, b);
		r = fabs(In - I2n)/3;
	}
	printf("| %.9f | %.3f | %.9f |\n", delta, 0.5*(b - a)/n, fabs(Io - I2n));
	printf("=====================================\n");
}