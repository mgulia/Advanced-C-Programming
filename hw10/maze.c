#include <stdio.h>
#include "maze.h"
#include <stdlib.h>

//void _find_maze_dimensions(FILE * fp, int * rows, int * cols);

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



Maze* malloc_maze(int num_rows, int num_cols)
{
	Maze* maze = malloc(sizeof(*maze)); 

	if (maze == NULL)
	{
		free(maze);
	}

	//initializes num_cols and num_rows
	maze->num_cols = num_cols;
	maze->num_rows = num_rows;
	
	maze->cells = malloc(sizeof(maze->cells)*num_rows);
	
	//checks if null
	if(maze->cells == NULL)
	{
		free(maze->cells);
	}
	
	//allocates memory
	for(int i=0; i<num_rows; i++)
	{
		maze->cells[i] = malloc(sizeof(maze->cells[i])*num_cols);
		if(maze->cells[i]==NULL)
		{
			free(maze->cells[i]);
		}

	}

	return maze;
}

void free_maze(Maze* maze)
{

	int num_rows = maze->num_rows;
	
	//free's allocated memory
	for(int i = 0; i<num_rows; i++)
	{
		free(maze->cells[i]);
	}
	
	//frees memory
	free(maze->cells);
	free(maze);

	return;
}


Maze* read_maze(FILE* fp)
{
	int rows = 0;
	int cols = 0;
	find_maze_dimensions(fp, &rows, &cols);
	
	//allocates memory
	Maze* maze = malloc_maze(rows, cols);
	
	rewind(fp);
	
	//reads the file
	for(int i = 0; i<maze->num_rows; i++)
	{
		int k = 0;
		while(k<maze->num_cols)
		{
			char c= fgetc(fp);
			maze->cells[i][k] = c;
			k++;
		}

		char ch = fgetc(fp);
		if(ch == '\n')
		{}
	}

	return maze;

}

bool write_maze(const char* filename, const Maze* maze)
{
	//opens file
	FILE* fp = fopen(filename, "a");
	if(fp == NULL)
	{
		return false;
	}

	int rows = maze->num_rows;
	int cols = maze->num_cols;
	
	//writes file
	for(int i = 0; i<rows; i++)
	{
		for(int k = 0; k<cols; k++)
		{
			char c = maze->cells[i][k];
			fputc(c, fp);
		}

		fputc('\n', fp);
	}

	//closes file
	fclose(fp);

	return true;
}

Maze* make_taller(const Maze* orig)
{
	int rows = orig->num_rows;
	int cols = orig->num_cols;
	int boundary = (orig->num_rows * 2) - 1;

	//allocates memory
	Maze* maze = malloc_maze((rows * 2) - 1, cols);
		
	//copies it vertically
	for(int i = 0; i<maze -> num_rows; i++)
	{
		for(int k = 0; k <= maze ->num_cols; k++)
		{
			maze -> cells[i][k] = orig->cells[i][k];
			maze -> cells[boundary - i - 1][k] = orig->cells[i][k];
		}

		maze -> cells[i][orig->num_cols] = '\n';
		maze -> cells[boundary - i - 1][orig->num_cols] = '\n';
	}

	return maze;

}


Maze* make_wider(const Maze* orig)
{
	//allocates memory
	Maze* maze = malloc_maze(orig->num_rows, (orig->num_cols * 2) - 1);

	int r = 0;
	int c = 0;

	
	for(int i = 0; i < orig->num_rows; i++)
	{
		for (int j = 0; j<orig->num_cols; j++)
		{
			maze->cells[r][c] = orig->cells[i][j];
			c++;
		}

		for(int k = orig->num_cols - 2; k >= 0; k--)
		{
			maze->cells[r][c] = orig->cells[i][k];
			c++;
		}

		r++;
		c = 0;
	}

	int row_diff = ((orig->num_rows + 1)/2) - 1;
	int column_diff = orig -> num_cols - 1;
	maze->cells[row_diff][column_diff] = PATH;

	int i = 1;
	int j = 1;
	int count = 0;

	//copies it horizontally
	while(count < maze -> num_cols - 1)
	{
		if(maze->cells[row_diff - 1][column_diff - i] == PATH ||maze -> cells[row_diff + 1][column_diff - i] == PATH){
			maze -> cells[row_diff][column_diff - i] = PATH;
		}

		else if(maze->cells[row_diff-1][column_diff-i] == WALL && maze->cells[row_diff+1][column_diff-i] == WALL){
				maze->cells[row_diff][column_diff - i] = PATH;
				i++;
		}

		if(maze->cells[row_diff - 1][column_diff + j] == PATH || maze->cells[row_diff+1][column_diff+j] == PATH)
		{
			maze->cells[row_diff][column_diff+j] = PATH;
		}


		else if(maze->cells[row_diff-1][column_diff+j] == WALL && maze->cells[row_diff+1][column_diff+j] == WALL){
				maze->cells[row_diff][column_diff + j] = PATH;
				j++;
		}

		count++;
	}

		return maze;

}





