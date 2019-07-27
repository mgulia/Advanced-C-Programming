//Global declaration

#include <stdio.h>

void print_integer(int n, int radix, char* prefix)
{

	//Outputs if it's a negative number	
  	if (n<0)
  	{
    	n = n * -1;
		fputc(45, stdout);
  	}

 	//Local Declrations	
	int power = 1; //used to determine exponent value
  	int i = 0; //counter for while loop
  	int divisor = 0; //divisor for algorithm when converting
  	int quotient = n; //quotient for algorithm when converting
  	int convert = 0; //index which will acquire converted value
  	int remainder; //remainder used in algorithm when converting
  	char set[] = "0123456789abcdefghijklmnopqrstuvwxyz"; //used for final conversion values
	
  	//Outputs the prefix
  	int count = 0;
  	if (prefix[count] != 0)
  	{
		while(count!=-1)
		{
			fputc(prefix[count], stdout);
			count++;
		
			if(prefix[count]==0)
			{
				count = -1;
			}
		}
	}

	//Calculates exponent used for later calculations
	while (power <= n)
	{	
		power = power * radix;
		i++;
	}
	
	divisor = 1;
	
	if (n == 1)
	{
		i = 1;
	}

	if (n == 0)
	{
		i = 0;
	}

	//converts the number
	while (i>=0)
	{
		//code here was used as a power function
		i--;
		for(int j = 1; j<=i; j++)
		{
			if (i == 1)
			{
				divisor = radix;
			
			}

			else
			{
				divisor = divisor * radix;
			}
		}

		if (i==0)
		{
			divisor = 1;
		}
		
		convert = quotient / divisor;
		
		//does calculation for conversion
		if (i>=0)
		{
			convert = convert * 1;
			remainder = quotient % divisor;
			quotient = remainder;
			divisor = 1;

			fputc(set[convert], stdout);

		}
	}
}


