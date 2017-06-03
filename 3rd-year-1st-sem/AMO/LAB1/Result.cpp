#include "Result.h"

Result& Result::operator=(Result& src) 
{
	if (this == &src) return src;
	f_x = src.f_x;
	n = src.n;
	absEr = src.absEr;
	remT = src.remT;

	return src;
}

Result::~Result() {};
Result::Result() {};