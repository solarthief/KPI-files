#pragma once

struct Result
{
	double x;
	double clarRoot;
	int count;

	Result(void);
	Result(Result& source);
	Result& operator=(Result& source);
	~Result(void);
};