#include "maze.h"
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char **argv)
{
	FILE* fp = fopen("sample.2.7X9", "r");
	
	if(fp == NULL)
	{
		return 0;
	}
	
	Maze* maze = read_maze(fp);

	for(int i = 0; i<(*maze).num_rows; i++)
	{
		for(int k = 0; k<(*maze).num_cols; k++)
		{
			printf("%c", (*maze).cells[i][k]);
		}

		printf("\n");
	}

	printf("\n");

	Maze* new = make_taller(maze);
	write_maze(argv[2], new);
	
	for(int i = 0; i<(*new).num_rows; i++)
	{
		for(int k = 0; k<(*new).num_cols; k++)
		{
			printf("%c", (*new).cells[i][k]);
		}

		printf("\n");
	}

	printf("\n");
	
	Maze* new2 = make_wider(maze);
	write_maze(argv[2], new2);

	for(int i = 0; i<(*new2).num_rows; i++)
	{
		for(int k = 0; k<(*new2).num_cols; k++)
		{
			printf("%c", (*maze).cells[i][k]);
		}

		printf("\n");
	}

	fclose(fp);

	free_maze(new);
	free_maze(new2);
	free_maze(maze);


	return 0;



}
