#include <iostream>
#include <stdio.h>
#include "methods.h"
#include "math.h"
#define N 4

using namespace std;

double fx(double x) 
{
	return 3/(2 + cos(x)) - (x/4);
}

double minus_fx(double x) 
{
	return -3/(2+cos(x))+(x/4);
}

int main() 
{
	double x;
	double	eps;
	double a, b;
	int i;
	Method *method = new Method();
	Result result, result2;
	
	cout<<"\t\tIteration Method"<<endl;
	cout<<endl;
	x = 5;
	cout<<"\tEps\t"<<"\t"<<"   Root's value\t"<<"\tEstimation accuracy"<<endl;
	for(i = 0, eps = 1e-2; i <= N; ++i, eps /= 1e3) {
		result = method->Iteration(0.7, 1.3, x, eps, minus_fx);
		printf("%.14lf \t %.15lf \t %.15lf\n", eps, result.x, result.clarRoot);
	}
	cout<<endl;

	x = 8;
	cout<<"\tEps\t"<<"\t"<<"   Root's value\t"<<"\tEstimation accuracy"<<endl;
	for(i = 0, eps = 1e-2; i <= N; ++i, eps /= 1e3) {
		result = method->Iteration(0.2, 1.1, x, eps, fx);
		printf("%.14lf \t %.15lf \t %.15lf\n", eps, result.x, result.clarRoot);
	}
	cout<<endl;

	x = 9.5;
	cout<<"\tEps\t"<<"\t"<<"   Root's value\t"<<"\tEstimation accuracy"<<endl;
	for(i = 0, eps = 1e-2; i <= N; ++i, eps /= 1e3) {
		result = method->Iteration(0.05, 1.5, x, eps, minus_fx);
		printf("%.14lf \t %.15lf \t %.15lf\n", eps, result.x, result.clarRoot);
	}
	cout<<endl;
	


	cout<<"\t\tBisection Method"<<endl;
	cout<<endl;
	a = 4;
	b = 6;
	cout<<"\tEps\t"<<"\t"<<"   Root's value\t"<<"\tEstimation accuracy"<<endl;
	for(i = 0, eps = 1e-2; i <= N; ++i, eps /= 1e3) {
		result = method->Bisection(a, b, eps, fx);
		printf("%.14lf \t %.15lf \t %.15lf\n", eps, result.x, result.clarRoot);
	}
	cout<<endl;

	a = 7;
	b = 9;
	cout<<"\tEps\t"<<"\t"<<"   Root's value\t"<<"\tEstimation accuracy"<<endl;
	for(i = 0, eps = 1e-2; i <= N; ++i, eps /= 1e3) {
		result = method->Bisection(a, b, eps, minus_fx);
		printf("%.14lf \t %.15lf \t %.15lf\n", eps, result.x, result.clarRoot);
	}
	cout<<endl;

	a = 9;
	b = 11;
	cout<<"\tEps\t"<<"\t"<<"   Root's value\t"<<"\tEstimation accuracy"<<endl;
	for(i = 0, eps = 1e-2; i <= N; ++i, eps /= 1e3) {
		result = method->Bisection(a, b, eps, minus_fx);
		printf("%.14lf \t %.15lf \t %.15lf\n", eps, result.x, result.clarRoot);
	}
	cout<<endl;



	cout<<"\tComparison Table "<<endl;
	cout<<endl;
	x = 5;
	a = 4;
	b = 6;
	cout<<"\tEps\t"<<"\t"<<"Iteration method\t"<<"Bisection method"<<endl;
	for(i = 0, eps = 1e-2; i <= N; ++i, eps /= 1e3) {
		result = method->Iteration(0.7, 1.3, x, eps, minus_fx);
		result2 = method->Bisection(a, b, eps, fx);
		printf("%.14lf \t %d \t\t\t %d\n", eps, result.count, result2.count);
	}

	return 0;
}