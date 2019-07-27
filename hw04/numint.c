// do not change this part, if you do, your code may not compile
//
/* test for structure defined by student */
#ifndef NTEST_STRUCT 
#include "numint.h"
#else 
#include "numint_key.h"
#endif /* NTEST_STRUCT */
//
// do not change above this line, if you do, your code may not compile
// This is the only file you have to include 

double simpson_numerical_integration(Integrand intg_arg)
{
	//Local declarations and calculations

	double integral = 0.0;
	
	double lower_limit = intg_arg.lower_limit;
	double upper_limit = intg_arg.upper_limit;
	double n_intervals = intg_arg.n_intervals;
	
	double width = (upper_limit - lower_limit) / n_intervals;
	double multiplier = width / 6;
	
	double leftBound = lower_limit;
	double rightBound = leftBound + width;
	double midpoint = (leftBound + rightBound) / 2;

	double a = 1;

	//Simpson algorithm
	for(int i = 0; i<n_intervals; i++)
	{
		double f_left = intg_arg.func_to_be_integrated(leftBound);
		double f_right = intg_arg.func_to_be_integrated(rightBound);
		double f_mid = intg_arg.func_to_be_integrated(midpoint);
		
		double simpson = multiplier * (f_left + 4*f_mid + f_right);

		integral += simpson;


		//Updates variables 
		leftBound = lower_limit +  (width * (a));
		rightBound = lower_limit + (width * (a+1));
		midpoint = (leftBound + rightBound) / 2;
		
		a++;
	}

	return integral;
}
