#include <stdio.h>
#include <stdlib.h>
#include "aux.h"
#include "util.h"
#include "fourier.h"

int main(int argc, char ** argv) {

	//Makes sure argc has 6 components
	if (argc != 6)
	{
		EXIT_FAILURE;
	}
   	
	//initializes struct
	Integrand integrand;

	int n_terms = atoi(argv[5]);

	//makes sure n_terms is 1
	if (n_terms <= 1)
	{
		n_terms = 1;
	}

	//checks which unknown function is being called
	if (argv[1][0] == '1' && argv[1][1] == '\0')
	{
		integrand.func_to_be_integrated = unknown_function_1;
	}

	else if (argv[1][0] == '2' && argv[1][1] == '\0')
	{
		integrand.func_to_be_integrated = unknown_function_2;
	}

	else if (argv[1][0] == '3' && argv[1][1] == '\0')
	{
		integrand.func_to_be_integrated = unknown_function_3;
	}

	else
	{
		return  EXIT_FAILURE;
	}

	//assigns values to lower_limit, upper_limit and n_intervals
	integrand.lower_limit = atof(argv[2]);
	integrand.upper_limit = atof(argv[3]);
	integrand.n_intervals = atoi(argv[4]);

	//makes sure integrand.n_intervals is equal to 1
	if(integrand.n_intervals < 1)
	{
		integrand.n_intervals = 1;
	}

	//defines fourier struct
	Fourier fourier = {
		.intg      = integrand,
		.n_terms   = n_terms,
		.a_i       = malloc(sizeof(*fourier.a_i) * n_terms), //***
		.b_i       = malloc(sizeof(*fourier.b_i) * n_terms)
	};


	//Exits if one fourier.a_i or fourier.b_i has a null value
	if (fourier.a_i == NULL || fourier.b_i == NULL) 
	{
		free(fourier.a_i); 
		free(fourier.b_i);
		
		return EXIT_FAILURE;
	}

	//Calls function and prints output
	fourier_coefficients(fourier);
	print_fourier_coefficients(fourier.a_i, fourier.b_i, fourier.n_terms);

	free(fourier.a_i);
	free(fourier.b_i);

   return EXIT_SUCCESS;
} 
