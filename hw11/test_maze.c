#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "maze.h"

int find_path_from_top_entrance_to_bottom_exit(char *maze_file, char *directions_file, char *visited_file);

int main(int argc, char* argv[]) 
{
	
	//declares values	
	Coord source;
	Coord dest;
	char *source_row;
	char *source_col;
	char *dest_row;
	char *dest_col;

   if (argc < 2) 
   {
       return EXIT_FAILURE;
   }
   
	
   	if(strcmp("-m", argv[1]) != 0 && strcmp("-s", argv[1])!=0)
	{
		return EXIT_FAILURE;
	}

	//simulation call
	if(strcmp("-s", argv[1]) == 0)
	{
		source.row = strtol(argv[5], &source_row, 10);
		source.col = strtol(argv[6], &source_col, 10);
		dest.row = strtol(argv[7], &dest_row, 10);
		dest.col = strtol(argv[8], &dest_col, 10);
	
		if (argc != 9)
		{
			return EXIT_FAILURE;
		}

		int numSteps = simulate_movement(argv[2], argv[3], argv[4], source, dest);
		printf("%d", numSteps);
	
	}

	//dfs call
	else if(strcmp("-m", argv[1]) == 0)
	{
		if (argc != 8)
		{
			return EXIT_FAILURE;
		}

		source.row = strtol(argv[4], &source_row, 10);
		source.col = strtol(argv[5], &source_col, 10);
		dest.row = strtol(argv[6], &dest_row, 10);
		dest.col = strtol(argv[7], &dest_col, 10);

		int shortestPath = dfs_shortest_path_directions(argv[2], argv[3], source, dest);
		printf("%d", shortestPath);

	}




	return EXIT_SUCCESS;
}
