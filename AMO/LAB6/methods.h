#pragma once
#pragma once
#include <iostream>
#include <cmath>
#include <fstream>

double func(double x);
double* defineA(double a, double b, int n);
double* defineC(double* A, double a, double b, int n);
double* defineD(double* C, double a, double b, int n);
double* defineB(double* A, double* C, double* D, double a, double b, int n);
double** defineSMatrix(double* A, double a, double b, int n);
double* gauss_elemination(double** A, int n);
double getInt(double x, double a, double b, int n, double*A, double*B, double*C, double*D);
