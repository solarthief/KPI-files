#include "methods.h"
using namespace std;
int main()
{
	int index, sub_index, si = 0, sj = 0;
	double eps = 0.001;
	double MATRIX[M][N] = {{11.0,5.0,1.0,20.0,75.0 }, 
				  	  {19.0,57.0,19.0,18.0,437.0}, 
					  {6.0,10.0,33.0,16.0,117.0 }, 
					  {15.0,14.0,5.0,14.0,149.0}};

	double **S_MATRIX = new double*[M]; 
	for (index = 0; index < N; index++) S_MATRIX[index] = new double[N];
	for(index = 0; index < M; index++) 
		for(sub_index = 0; sub_index < N; sub_index++) 
			S_MATRIX[index][sub_index] = MATRIX[index][sub_index];

	double *x=new double[M];
	for(index = 0; index < M; index++) x[index] = 0.0;

	cout<<"         Gaussian Elimination Method        "<<endl;
	cout << "       x1       " << "       x2       " << "       x3       " << "       x4       " << endl;
	cout<<"-------------------------------------------------------------------"	<<endl;
	gaussian_elimination(S_MATRIX, x, si, sj);
	for (index = 0; index < M; index++)	cout<<setw(14)<<x[index]<<" | ";
	cout<<endl<<"-------------------------------------------------------------------"<<endl<<endl;


	cout<<"         Gauss-Seidel Method        "<<endl;
	cout << "       x1       " << "       x2       " << "       x3      " << "         x4       " << endl;
	cout<<"-------------------------------------------------------------------"<<endl;
		gauss_seidel(MATRIX, x, eps);
	for (index = 0; index < M; index++)
		cout<<setw(14)<<x[index]<<" | ";
	cout<<endl<<"-------------------------------------------------------------------"<<endl;

	system("PAUSE");
	return 0;
}