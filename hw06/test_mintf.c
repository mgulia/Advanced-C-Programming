
//Global declarations

#include <stdio.h>
#include <limits.h>
#include <stdlib.h>
#include "mintf.h"

int main(int argc, char* argv[])
{
	//Test cases; prints new line
	
	mintf("2017");
	printf("\n");
	
	mintf("Star Wars incoming in %d!", 2017);
	printf("\n");
	
	mintf("%s is gonna be grey jedi in %d", "Luke", 2017);

	mintf("Rey's gonna turn to the dark side 100%%%%%%%%.");
	printf("\n");
	
	mintf("I'm gonna be %b in the theater.", 12345);
	printf("\n");
	
	mintf("%s need's to get a haircut before %d", "Kylo Ren", 2017);
	printf("\n");
	
	mintf("R2D2 is genius, worth %$.", 124.568);
	printf("\n");	

	mintf("Kylo Ren gonna go from %d to %d", 100, -100);
	printf("\n");
	
	mintf("The ticket better cost %$.", -500);
	printf("\n");
	
	mintf("Too many numbers: %d", 2017, 2017, 2017);
	printf("\n");

	mintf("This is straight up hex %x", 2017);
	printf("\n");

	mintf("Star Wars is gonna be %c plus", 'A');

	//Exits success
	return (EXIT_SUCCESS);
}

