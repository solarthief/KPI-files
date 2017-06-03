#include "Result.h"

Result::Result(Result& source) 
{
	x = source.x;
	clarRoot = source.clarRoot;
	count = source.count;
}

Result& Result::operator=(Result& source) 
{
	if (this == &source)
		return source;
	x = source.x;
	clarRoot = source.clarRoot;
	count = source.count;
	return source;
}

Result::~Result(void) {}

Result::Result(void) {}