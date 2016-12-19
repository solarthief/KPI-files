#ifndef _METHODS_H
#define _METHODS_H
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <cmath>
#include <iostream>
#include <fstream>
#include <ios>
#include <iomanip>
#define methods
#define M 4
#define N 5
void gaussian_elimination(double **MATRIX, double x[M], int si, int sj);
void gauss_seidel(double MATRIX[M][N], double x[M], double eps);
#endif
