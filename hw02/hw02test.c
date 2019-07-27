//Global declarations

#include <stdio.h>
#include <limits.h>
#include <stdlib.h>
#include "hw02.h"

int main(int argc, char* argv[])
{
	//Test cases; prints new line
	
	print_integer(-46656, 36, "");
	printf("\n");

	print_integer(4, 2, "");
	printf("\n");
	
	print_integer(-534.654, 10, "@&");
	printf("\n");
	
	print_integer(534654, 16, "");
	printf("\n");

	print_integer(534654, 16, "$b");
	printf("\n");

	print_integer(-534654, 16, "&$");
	printf("\n");

	print_integer(-534654, 2, "hola");
	printf("\n");

	print_integer(534, 10, "");
	print_integer(-654, 10, "");
	printf("\n");

	return (EXIT_SUCCESS);
}

