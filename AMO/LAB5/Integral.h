#pragma once
#include <math.h>
#include <iostream>
#include <fstream>
#include <functional>
using namespace std;
double I(double a, double b, int n, function<double(double)> f);
double integrate(double a, double b, double eps, function<double(double)> f);