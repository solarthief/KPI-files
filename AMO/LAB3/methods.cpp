#include "methods.h"


void gaussian_elimination(double **MATRIX, double x[M], int si, int sj)
{
	int index, sub_index;
	double tmp;
	
	tmp = MATRIX[si][sj];
	for(sub_index = sj; sub_index < N; sub_index++) MATRIX[si][sub_index] = MATRIX[si][sub_index]/tmp;
	
	for(index = si+1; index < M; index++)
	{
		tmp = MATRIX[index][sj];
		for(sub_index = sj; sub_index < N; sub_index++) 
			MATRIX[index][sub_index] = MATRIX[index][sub_index] - tmp * MATRIX[si][sub_index];
	}
	
	if (si < M)	gaussian_elimination(MATRIX, x, ++si, ++sj);
	
	si -= 1;
	sj -= 1;
	tmp = 0.0;
	for(index = 0; index < (M-si-1); index++) 
		tmp = MATRIX[si][sj+index+1]*x[si+index+1] + tmp; 	
	x[si] = MATRIX[si][N-1] - tmp;
	return;
}

//Gauss-Seidel Method
void gauss_seidel(double MATRIX[M][N], double x[M], double eps)
{
	int i, j;
	double tmp2, maxx;
	double **S_MATRIX = new double*[M]; 
	for (i = 0; i < N; i++)	S_MATRIX[i] = new double[N];
	double *tmp = new double[M]; 
	for (i = 0; i < M; i++)	tmp[i] = 0.0;
	
	for(i = 0; i < M; i++)
		if((i == 1) || (i == 2)) 
			for(j = 0; j < N; j++)
				S_MATRIX[i][j] = MATRIX[i][j];
	for(j = 0; j < N; j++)	S_MATRIX[0][j] = MATRIX[0][j] + 2*MATRIX[2][j] - 5 * MATRIX[3][j];
	for (j = 0; j < N; j++)	S_MATRIX[3][j] = MATRIX[3][j] + 3 * MATRIX[0][j] - MATRIX[1][j] - MATRIX[2][j] ;
	//vector beta
	double *beta;
	beta = new double[M];
	for (i = 0; i < M; i++)	beta[i] = S_MATRIX[i][N-1] / S_MATRIX[i][i];
	//matrix alfa
	double **alfa;
	alfa = new double*[M];
	for(i = 0; i < M; i++)	alfa[i] = new double[M];
	for(i = 0; i < M; i++)
		for(j = 0; j < M; j++)
		{
			if(i != j) alfa[i][j] = - S_MATRIX[i][j] / S_MATRIX[i][i];
			else alfa[i][j] = 0;
		};
	
	for(i = 0; i < M; i++)	x[i] =beta[i];
	
	double q = 0.0, max;
	for(i = 0; i < M; i++)
	{
		max = 0.0;
		for(j = 0; j < M; j++)	max = fabs(alfa[i][j]) + max;
		if(max > q)	q = max;
	};
	
	do
	{
		
		for(i = 0; i < M; i++) tmp[i] = x[i];
		
		for(i = 0; i < M; i++)
		{
			tmp2 = 0.0;
			for(j = 0; j < M; j++) if (i!=j) tmp2 = alfa[i][j] * x[j] + tmp2;
			x[i] = beta[i] + tmp2;
		};
		
		maxx = 0.0;
		tmp2 = 0.0;
		for(i = 0; i < M; i++)
		{
			tmp2 = fabs(tmp[i] - x[i]);
			if(tmp2 > maxx) maxx = tmp2;
		}
	} while(maxx > fabs((1 - q) * eps / q));
	return;
}
