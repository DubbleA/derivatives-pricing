//Random1.cpp

#include "Random.h"
#include <cstdlib>
#include <cmath>

#if !defined(_MSC_VER)
using namespace std;
#endif


double GetOneGaussianBySummation()
{
	double result = 0;
    
	for(unsigned long j=0;j<12;j++)
		result += rand()/static_cast<double>(RAND_MAX);
    
	result -= 6.0;
    
	return result;
}

double GetOneGaussianByBoxMuller()
{
	double result;
	double x, y;
	double sizeSquared = 1.0;
    
	while (sizeSquared >= 1.0) {
		x = 2.0 * rand()/static_cast<double>(RAND_MAX)-1;
		y = 2.0 * rand()/static_cast<double>(RAND_MAX)-1;
		sizeSquared = x*x + y*y;
	}
	result = x*sqrt(-2*log(sizeSquared)/sizeSquared);
    
	return result;
}