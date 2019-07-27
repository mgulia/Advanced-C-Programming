#include <math.h>
#include "fourier.h"
#define M_PI 3.141592653589793115997963468544185161590576171875L
double simpson_numerical_integration(Integrand intg_arg) {
	
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

	int a = 1;

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

double simpson_numerical_integration_for_fourier(Integrand intg_arg, int n, double (*cos_sin)(double)) 
{
	//Local Declarations
	double integral = 0.0;

	double halfPeriod = (intg_arg.upper_limit - intg_arg.lower_limit) / 2;
	
	double lower_limit = intg_arg.lower_limit;
	double upper_limit = intg_arg.upper_limit;
	double n_intervals = intg_arg.n_intervals;
	
	double width = (upper_limit - lower_limit) / n_intervals;
	double multiplier = width / 6;
	
	double leftBound = lower_limit;
	double rightBound = leftBound + width;
	double midpoint = (leftBound + rightBound) / 2;

	int a = 1;

	//Simpson algorithm with fourier
	for(int i = 0; i<n_intervals; i++)
	{
		double f_left = intg_arg.func_to_be_integrated(leftBound) * cos_sin((n * M_PI * leftBound) / halfPeriod); 
		double f_right = intg_arg.func_to_be_integrated(rightBound) * cos_sin((n * M_PI * rightBound) / halfPeriod);
		double f_mid = intg_arg.func_to_be_integrated(midpoint) * cos_sin((n * M_PI * midpoint) / halfPeriod);
		
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

void fourier_coefficients(Fourier fourier_arg) {


	//Calculates half of perioid and assign sub zero values
	double halfPeriod = (fourier_arg.intg.upper_limit - fourier_arg.intg.lower_limit) / 2;
  
	fourier_arg.a_i[0] = (simpson_numerical_integration(fourier_arg.intg)) * (1/halfPeriod);
	fourier_arg.b_i[0] = 0;

	//Assigns values for a and b after sub zero
	for (int i = 1; i < fourier_arg.n_terms; i++)
	{
		fourier_arg.a_i[i] = (1/halfPeriod) * simpson_numerical_integration_for_fourier(fourier_arg.intg, i, cos);
		fourier_arg.b_i[i] = (1/halfPeriod) * simpson_numerical_integration_for_fourier(fourier_arg.intg, i, sin);
	}
	

}
