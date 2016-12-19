#include "mainfunc.h"

double* gaussian_elimination(double **AM, int N) 
{
	int i, j, k, l;
	double tmp;
	double* res = new double[N];
	for (i = 0; i < N; i++)
	{
		tmp = AM[i][i];
		for (j = i; j < N + 1; j++) AM[i][j] /= tmp;

		for (k = i + 1; k < N; k++)
		{
			tmp = AM[k][i];
			for (l = i; l < N + 1; l++) AM[k][l] -= AM[i][l] * tmp;
		}
	}
	for (i = N - 1; i >= 0; i--)
	{
		tmp = 0;
		for (j = N - 1; j > i; j--) tmp += AM[i][j] * res[j];
		res[i] = AM[i][N] - tmp;
	}
	return res;
}