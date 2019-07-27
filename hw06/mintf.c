//#ifndef __mintf_h__
#define __mintf_h__
#include <stdarg.h>
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


//mintf function
void mintf(const char *format, ...)
{

	//variadic functions
	va_list convert_args;
	va_start(convert_args, format);


	int i = 0;

	//loops through the format array
	while(format[i] != '\0')
	{
		//checks to see if % is present.
		if (format[i] == '%' && format[i+1]!='\0')
		{
			//if so, it checks the next character and converts accordingly
			if (format[i+1] == 'd')
			{
				//pulls out int using variadic function and passes it into print_integer
				int num = va_arg(convert_args, int);
				print_integer(num, 10, "");	
			}

			else if (format[i+1] == 'x')
			{
				int num = va_arg(convert_args, int);
				print_integer(num, 16, "0x");
			}

			else if (format[i+1] == 'b')
			{
				int num = va_arg(convert_args, int);
				print_integer(num, 2, "0b");
			}
		

			else if (format[i+1] == '$')
			{
			
				//separates the numbers before and after the decimal sign and puts them together
				double num = va_arg(convert_args, double);
				int firstPart = (int)num;

				double secondPart = (firstPart - num) * 100;
		
				if(secondPart<0)
				{
					secondPart *= -1;
				}
			
				int secondPartCast = (int)secondPart;
				print_integer(firstPart, 10, "$");
				fputc('.', stdout);
				print_integer(secondPartCast, 10, "");
			
			}
		
			
			else if (format[i+1] == 's')
			{
				//pulls out array and loops through it
				char* string = va_arg(convert_args, char*);
				int count = 0;
				
				while(string[count] != '\0')
				{
					fputc(string[count], stdout);
					count++;
				}
			}

		
			else if (format[i+1] == 'c')
			{
				int num = va_arg(convert_args, int);
				char ch = num;

				fputc(ch, stdout);
			}
			
			else
			{
				//prints out % sign
				fputc(format[i], stdout);
				//prints out next value if it's not a % sign. So z in %z.
				if (format[i+1] != '%')
				{
					fputc(format[i+1], stdout);
				}
			}


			i++;

		}

		
		//if % is not involved then it prints out whatever is in the array of format
		else
		{
			fputc(format[i], stdout);
		}

		i++;
	}
	

}
