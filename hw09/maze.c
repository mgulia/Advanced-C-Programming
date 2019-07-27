#include <stdio.h>
#include <stdlib.h>
#include "maze.h"

void find_maze_dimensions(FILE * fp, int * a_num_rows, int * a_num_cols) 
{
	//uses fseek to initialize it to 0
	fseek(fp, 0, SEEK_SET);
	*a_num_rows = *a_num_cols = 0;
	
	//sets count to fgetc(fp)
	char count = fgetc(fp);

	//checks the boundaries and dimensions
	while (count != EOF)
	{
		if (count != '\n')
		{
			if(*a_num_rows == 0)
			{
				(*a_num_cols)++;
			}
		}

		else
		{
			(*a_num_rows)++;
		}

		count = fgetc(fp);
	}
}


int find_opening_location(FILE * fp) 
{
	  	
	fseek(fp, 0, SEEK_SET);

	char count = fgetc(fp);
	int open = 0;

	//determines the column location of the top opening
	while (count != PATH)
	{
		open++;
		count = fgetc(fp);	
		
	}
	
	return open;

}

int count_path_locations(FILE * fp) 
{

	fseek(fp, 0, SEEK_SET);
	int i = 0;
	char count = fgetc(fp);

	//counts the number of locations that are PATH
	while(count!=EOF)
	{
		if(count == PATH)
		{
			i++;
		}

		count = fgetc(fp);
	}
	
	return i;

}

char get_location_type(FILE * fp, int row, int col) 
{

	fseek(fp, 0, SEEK_SET);
	int count = fgetc(fp);
	int r_copy = 0;
	int c_copy = 0;
	char c_type = 'x';

	//Increments the row
	while( r_copy < row)
	{
		while(count <= '\n')
		{
			count = fgetc(fp);
		}

		r_copy++;
	}

	//Increments the column
	while(c_copy < col)
	{
		count = fgetc(fp);
		c_copy++;
	}

	//Returns the type of location: WALL/PATH
	if(count == PATH)
	{
		c_type = PATH;
	}

	else if(count == WALL)
	{
		c_type = WALL;
	}

	return c_type;

}
 
int represent_maze_in_one_line(char * filename, FILE * fp) 
{

	fseek(fp, 0, SEEK_SET);
	int i = 0;
	FILE * file;
	char count = fgetc(fp);
	file = fopen(filename, "w");

	//if null return
	if(file == NULL)
	{
		return MAZE_WRITE_FAILURE;
	}

	//writes a copy of the maze to a new file
	while(count != EOF)
	{
		if(count != '\n')
		{
			i++;
			fputc(count, file);
		}

		count = fgetc(fp);
	}


	fclose(file);

	return i;

}
