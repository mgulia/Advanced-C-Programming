#include "numint.h"
#include "aux.h"
//
// The function performs numerical integration of the function double
// function_to_be_integrated(double) over the range lower_limit to upper_limit using
// the mid-point rule
//
// The range is divided into n_intervals uniform intervals, where the left-most
// interval has a left boundary of lower_limit and the right-most interval has a
// right boundary of upper_limit (assuming lower_limit <= upper_limit).  If
// lower_limit >= upper_limit, the right-most interval has a right boundary of
// lower_limit and the left-most interval has a left boundary of upper_limit.
// 
// The mid-point rule is used to perform the integration for each interval.  In the
// mid-point rule, the integration is approximated by using the area of a rectangle,
// where the height of the rectange is obtained by
// function_to_be_integrated(mid-point of the interval).  The width of the rectangle
// is (interval boundary closer to upper_limit - interval boundary closer to
// lower_limit).  Note that width could be negative if upper_limit < lower_limit
//
// The integral is the sum of the integration over all intervals.
//
// The caller function has to make sure that n_intervals >= 1.  Therefore, this
// function may assume that n_intervals >= 1
//
double mid_point_numerical_integration(double lower_limit, double upper_limit, int n_intervals)
{
	//Local declarations
	double integral = 0.0;//integral value
	double width; //delta x
	double a; //used for simplicity
	double midpoint; //midpoint
	double sum; //sum of f(x) values
	double lower; //used for lower bound in calc
	double upper; //used for upper bound in calc
	
	//Upper>Lower calculations
	//calculates the midpoint, f(x) and sums up f(x)
	if(upper_limit>=lower_limit)
	{
		width = (upper_limit - lower_limit) / n_intervals;
		a = lower_limit;
		lower = a;
		upper = a + width;
		midpoint = (lower + upper) / 2;

		for(int i = 0; i<n_intervals; i++)
		{
			sum += function_to_be_integrated(midpoint);
			midpoint += width;
		}
	}

	//Lower>Upper Calculations
	//calculates the midpoint, f(x) and sums up f(x)
	else if(lower_limit>upper_limit)
	{
		width = (lower_limit - upper_limit) / n_intervals;
		a = upper_limit;
		lower = a;
		upper = a - width;
		midpoint = (lower + upper) / 2;

		midpoint = (a + width) / 2;

		for(int j = 0; j<n_intervals; j++)
		{
			sum += function_to_be_integrated(midpoint);
			midpoint -= width;
		}
	}

	//calculates the integral by multiplying the width
	integral = sum * width;

	return integral;
}

// 
// The function performs numerical integration of the function double
// function_to_be_integrated(double) over the range lower_limit to upper_limit using
// the trapezoidal rule.
//
// The range is divided into n_intervals uniform intervals, where the left-most
// interval has a left boundary of lower_limit and the right-most interval has a
// right boundary of upper_limit (assuming lower_limit <= upper_limit).  If
// lower_limit >= upper_limit, the right-most interval has a right boundary of
// lower_limit and the left-most interval has a left boundary of upper_limit.
// 
// The trapezoidal rule is used to perform the integration for each interval.  In the
// trapezoidal rule, the integration is approximated by the area of a trapezoid,
// where the heights of the parallel boundaries of the trapezoid are obtained by
// function_to_be_integrated(left boundary of the interval) and
// function_to_be_integrated(right boundary of the interval).  The width of the
// trapezoid is (interval boundary closer to upper_limit - interval boundary closer
// to lower_limit).  Note that width could be negative if upper_limit < lower_limit.
// The area of a trapezoid is the average of the two heights multiplied by the width.
//
// The integral is the sum of the integration over all intervals.
//
// The caller function has to make sure that n_intervals >= 1
// Therefore, this function may assume that n_intervals >= 1
//
double trapezoidal_numerical_integration(double lower_limit, double upper_limit, int n_intervals)
{
	//Local declarations
	double integral = 0.0; //integral
	double width; //delta x
	double multiplier; //used for calculating final integral value
	double sum; //sum of f(x) values

	//Upper>Lower calculations
	//created for loop and sums up f(x)
	if (upper_limit > lower_limit)
	{
		width = (upper_limit - lower_limit) / n_intervals;
		multiplier = width / 2;
		sum = 0;

		for(double i = lower_limit; i<=upper_limit; i+=width)
		{
			if (i == lower_limit || i == upper_limit)
			{
				sum += function_to_be_integrated(i);
			}

			else
			{
				sum += (2*function_to_be_integrated(i));
			}
		}		
	}
	
	//Lower>Upper
	//created for loop which sums up the f(x) values
	else if (lower_limit > upper_limit)
	{
		width = (lower_limit - upper_limit) / n_intervals;
		multiplier = width / 2;
		sum = 0;

		for (double j = lower_limit; j>=upper_limit; j--)
		{
			if (j == lower_limit || j == upper_limit)
			{
				sum += function_to_be_integrated(j);
			}

			else
			{
				sum += (2*function_to_be_integrated(j));
			}
		}
	}

	//multiplier is width/2
	//multiplying it with the sum gives the integral value
	integral = multiplier * sum;

	return integral;
}
