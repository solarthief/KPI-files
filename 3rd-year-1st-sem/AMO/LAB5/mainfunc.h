#pragma once
#include <math.h>
#include <iostream>
#include <fstream>
#include <functional>
#include "Matrixsolv.h"
#include "Integral.h"

using namespace std;


double lejandr(int n, double x);
double* createconstA(double a, double b, double eps, int N, function<double(double)> f);
double val(double*A, double x, int N);