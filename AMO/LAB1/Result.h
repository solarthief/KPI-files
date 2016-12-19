
struct Result
{
	double f_x;
	int n;
	double absEr;
	double remT;

	Result();
	~Result();
	Result& operator=(Result& src);	
};
