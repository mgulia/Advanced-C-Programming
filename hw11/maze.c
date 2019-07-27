#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>
#include "maze.h"

static bool is_path(Maze *maze, int row, int col)
{
   if ((row >= 0) && (row < maze->n_row)) {
      if ((col >= 0) && (col < maze->n_col)) {
         return maze->maze_array[row][col] == PATH;
      }
   }
   return false;
}


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
	maze->n_col = num_cols;
	maze->n_row = num_rows;
	
	maze->maze_array = malloc(sizeof(maze->maze_array)*num_rows);
	
	//checks if null
	if(maze->maze_array == NULL)
	{
		free(maze->maze_array);
	}
	
	//allocates memory
	for(int i=0; i<num_rows; i++)
	{
		maze->maze_array[i] = malloc(sizeof(maze->maze_array[i])*num_cols);
		if(maze->maze_array[i]==NULL)
		{
			free(maze->maze_array[i]);
		}

	}

	return maze;
}

void free_maze(Maze* maze)
{

	int num_rows = maze->n_row;
	
	//free's allocated memory
	for(int i = 0; i<num_rows; i++)
	{
		free(maze->maze_array[i]);
	}
	
	//frees memory
	free(maze->maze_array);
	free(maze);
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
	for(int i = 0; i<maze->n_row; i++)
	{
		int k = 0;
		while(k<maze->n_col)
		{
			char c= fgetc(fp);
			maze->maze_array[i][k] = c;
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
	FILE* fp = fopen(filename, "w");
	if(fp == NULL)
	{
		return false;
	}

	int rows = maze->n_row;
	int cols = maze->n_col;
	
	//writes file
	for(int i = 0; i<rows; i++)
	{
		for(int k = 0; k<cols; k++)
		{
			char c = maze->maze_array[i][k];
			fputc(c, fp);
		}
		//if statement if it fails fputc
		fputc('\n', fp);
	}

	//closes file
	fclose(fp);

	return true;
}


/* given a maze, current row (curr),                                     */
/* current column (curc), destination row (drow), destination col (dcol) */
/* current distance from source, determine the where to explore from the */
/* current location                                                      */
/* a recursive function: from the current location, try 'N', 'S', 'E',   */
/* 'W' locations one at a time if the attempt is successful, write the   */
/* direction in the file                                                 */
static int _pathfinder_helper(Maze *maze, int curr, int curc, int endr, int endc,
                            int count, FILE *dfptr, int flag)
{
   // you may uncomment this and use the output here to trace the function
   // with sample5.pdf
   // printf("(%d, %d), %d\n", curr, curc, count);
   maze->maze_array[curr][curc] = VISITED;
   if ((curr == endr) && (curc == endc)) { // reach the destination 
      int i;
	  if (flag == 1)
	  {
      	for (i = 0; i < count; i++) { // create enough space in file
         	fputc(VISITED, dfptr);
      	}
	  }
	  
   	maze->maze_array[curr][curc] = PATH;
      return count;

   }

	
   int found_n = INT_MAX;
   int found_s = INT_MAX;
   int found_e = INT_MAX;
   int found_w = INT_MAX;

   //gets value for each respective direction
		
   if (is_path(maze, curr-1, curc)) 
   {
	   
      found_n = _pathfinder_helper(maze, curr-1, curc, endr, endc, count+1, dfptr, 0);
	  /*
      if (found_n != -1) 
	  {
         fseek(dfptr, -1, SEEK_CUR); // go back one position
        // fputc('N', dfptr);
         fseek(dfptr, -1, SEEK_CUR); // go back one position
        // return found;
		

      }
	  */
		
   }

   if (is_path(maze, curr+1, curc)) 
   {
      found_s = _pathfinder_helper(maze, curr+1, curc, endr, endc, count+1, dfptr, 0);
	  /*
      if (found_s != -1) 
	  {
		 fseek(dfptr, -1, SEEK_CUR); // go back one position
       //  fputc('S', dfptr);
         fseek(dfptr, -1, SEEK_CUR); // go back one position
        // return found;
      }
	  
	  */

   }

   if (is_path(maze, curr, curc+1)) 
   {
      found_e = _pathfinder_helper(maze, curr, curc+1, endr, endc, count+1, dfptr, 0);
	  /*
      if (found_e != -1) 
	  {
         fseek(dfptr, -1, SEEK_CUR); // go back one position
        // fputc('E', dfptr);
         fseek(dfptr, -1, SEEK_CUR); // go back one position
        // return found;
      }
	  
	  */

   }

   if (is_path(maze, curr, curc-1)) 
   {
      found_w = _pathfinder_helper(maze, curr, curc-1, endr, endc, count+1, dfptr, 0);
	  /*
      if (found_w != -1) 
	  {
         fseek(dfptr, -1, SEEK_CUR); // go back one position
        // fputc('W', dfptr);
         fseek(dfptr, -1, SEEK_CUR); // go back one position
        // return found;
      }
	  */
   }
	
   	//DETERMINES MIN VALUE
	
   int found_array[4] = {found_n, found_s, found_e, found_w};
	
	int min = INT_MAX;
	
	for(int i=0; i<4; i++)
	{
		
		if(found_array[i] > 0 && found_array[i] < min)
		{
			min = found_array[i];	
		}
	}

	
	if(flag == 0)
	{
		//make equal to path
   		maze->maze_array[curr][curc] = PATH;
		return min;
	}

	
	//using the min it writes the direction in the direction file
	
	//FOUND_N MIN
	if (min == found_n)
	{
   		if (is_path(maze, curr-1, curc)) 
		{
      		found_n = _pathfinder_helper(maze, curr-1, curc, endr, endc, count+1, dfptr, 1);
      		if (found_n != -1) 
			{
         		fseek(dfptr, -1, SEEK_CUR); // go back one position
        		fputc('N', dfptr);
				fseek(dfptr, -1, SEEK_CUR); // go back one position
        		// return found;
      		}	
		}
	}
	
	//FOUND_S MIN 
	else if(min == found_s)
	{
		if (is_path(maze, curr+1, curc))
   		{
      		found_s = _pathfinder_helper(maze, curr+1, curc, endr, endc, count+1, dfptr, 1);
      		if (found_s != -1) 
	  		{
		 		fseek(dfptr, -1, SEEK_CUR); // go back one position
       			fputc('S', dfptr);
         		fseek(dfptr, -1, SEEK_CUR); // go back one position
        		// return found;
      		}
		}
	}

	//FOUND_E MIN
	else if(min == found_e)
	{
 
   		if (is_path(maze, curr, curc+1)) 
   		{
      		found_e = _pathfinder_helper(maze, curr, curc+1, endr, endc, count+1, dfptr, 1);
	  		
      		if (found_e != -1) 
	  		{
         		fseek(dfptr, -1, SEEK_CUR); // go back one position
        		fputc('E', dfptr);
         		fseek(dfptr, -1, SEEK_CUR); // go back one position
        		//return found;
  			}
			
		}
	}

	//FOUND_W MIN
	else if(min == found_w)
	{

   		if (is_path(maze, curr, curc-1)) 
   		{
      		found_w = _pathfinder_helper(maze, curr, curc-1, endr, endc, count+1, dfptr, 1);
      		if (found_w != -1) 
	  		{
         		fseek(dfptr, -1, SEEK_CUR); // go back one position
        		fputc('W', dfptr);
         		fseek(dfptr, -1, SEEK_CUR); // go back one position
        		//return found;
      		}
		}
	}
	
	
   	maze->maze_array[curr][curc] = PATH;
	return min;

 
}



/* this is a function implemented by the instructor to illustrate           */
/* how to use a recursive function to go from the left-most top entrance to */
/* the right-most bottom exit of a maze.  The function will print the       */
/* directions taken to reach the bottom exit, without visiting a location   */
/* twice.  Note that the recursion may visit a location a few times         */
/* Given three filenames, first one is a given maze, the second one is to   */
/* be written with the directions, the third is the explored maze           */
/* If the maze file does not exist, the function immediately return -1 and  */
/* do nothing else                                                          */
/* the directions are in the form of a series of characters                 */
/* 'N', 'S', 'E', 'W', without spacing (and without the quotes).            */
/* There should be just a single line, without a terminating newline        */
/* character. In other words, to the vi editor, it is an incomplete file    */
/* you are to assume that you start from the top-most, left-most entry      */
/* of the maze.  Therefore, the first direction is always 'S'               */
/* similarly, the last direction is always 'S'                              */
/* the returned value should be the number of steps taken to reach          */
/* the right-most bottom exit.  It is typically not the shortest distance   */
/* Note that the maze can be generated by amaze, or some combinations of    */
/* the maze expansion functions that you have written in PE08               */
/* you may assume that the maze file, if it exists, is in the correct format*/

int find_path_from_top_entrance_to_bottom_exit(char *maze_file, char *directions_file, char *visited_file)
{
   FILE *mfptr = fopen(maze_file, "r");
   if (mfptr == NULL) {
      return -1;
   }
   
   /* read the maze from mfptr */

   Maze *maze = read_maze(mfptr);
   fclose(mfptr);
   if (maze == NULL) {
      return -1;
   }
   
   /* find the starting location, the top-most, left-most opening */
   int startr, startc;
   startr = 0;
   for (startc = 0; startc < maze->n_col; startc++) {
      if (maze->maze_array[startr][startc] == PATH) {
         break;
      }
   }

   /* find the ending location, the bottom-most, right most opening */
   int endr, endc;
   endr = maze->n_row-1;
   for (endc = maze->n_col-1; endc >= 0; endc--) {
      if (maze->maze_array[endr][endc] == PATH) {
         break;
      }
   } 

   // no starting location, deallocate and return 
   if (startc == maze->n_col) {
      free_maze(maze);
      return -1;
   }
   // no ending location, deallocate and return 
   if (endc == -1) {
      free_maze(maze);
      return -1;
   }

   FILE *dfptr = fopen(directions_file, "w");
   if (dfptr == NULL) {
      free_maze(maze);
      return -1;
   }
   int steps = _pathfinder_helper(maze, startr, startc, endr, endc, 0, dfptr, 0);
   write_maze(visited_file, maze);
   fclose(dfptr);
   free_maze(maze);
   return steps;
}

int dfs_shortest_path_directions(char *maze_file, char *directions_file,
                        Coord source, Coord destination)
{
	//opens file
	FILE* fileMaze = fopen(maze_file, "r");
	if (fileMaze == NULL)
	{
		return -1;
	}
	
	Maze* maze = read_maze(fileMaze);
	fclose(fileMaze);
	if (maze == NULL)
	{
		return -1;
	}	


	FILE* directions = fopen(directions_file, "w");
	if (directions == NULL)
	{
		free_maze(maze);
		return -1;
	}

	//extracts data
	int start_row = source.row;
	int start_col = source.col;

	int dest_row = destination.row;
	int dest_col = destination.col;

	//checks if valid
	if(is_path(maze, start_row, start_col) == false)
	{
		return -1;
	}

	if(is_path(maze, dest_row, dest_col) == false)
	{
		return -1;
	}

	//calls helper function, closes directions and frees memory
	int num_steps = _pathfinder_helper(maze, start_row, start_col, dest_row, dest_col, 0, directions, 1);
	fclose(directions);
	free_maze(maze);

	return num_steps;
}

int simulate_movement(char *maze_file, char *directions_file, char *visited_file,
                      Coord source, Coord destination)
{
	//opens file
	
	FILE* fileMaze = fopen(maze_file, "r");
	if (fileMaze == NULL)
	{
		return -1;
	}

	Maze* maze = read_maze(fileMaze);
	fclose(fileMaze);
	if (maze == NULL)
	{
		return -1;
	}

	FILE* directions = fopen(directions_file, "r");
	if(directions == NULL)
	{
		free_maze(maze);
		return -1;
	}

	//extracts data
	int start_row = source.row;
	int start_col = source.col;

	int dest_row = destination.row;
	int dest_col = destination.col;
	
	//checks if valid
	if(is_path(maze, start_row, start_col) == false)
	{
		return -1;
	}

	if(is_path(maze, dest_row, dest_col) == false)
	{
		return -1;
	}

	int row = start_row;
	int col = start_col;

	int counter=0;

	fseek(directions, 0, SEEK_SET);

	int step = 0;
	bool tf;

	//puts dot
	maze->maze_array[row][col] = '.';
	counter++;
	while((step = fgetc(directions)) != EOF)
	{
		//goes through the maze, checks if valid and puts dot
		if(step == 'N')
		{
			row -= 1;
			tf = is_path(maze, row, col);
			if(tf == true)
			{
				maze->maze_array[row][col] = '.';	
				counter++;
			}
		}

		if(step == 'S')
		{
			row += 1;
			tf = is_path(maze, row, col);
			if(tf == true)
			{
				maze->maze_array[row][col] = '.';
				counter++;
			}

			
		}

		if(step == 'E')
		{
			col += 1;
			tf = is_path(maze, row, col);
			
			if(tf == true)
			{
				maze->maze_array[row][col] = '.';
				counter++;
			}

		}

		if(step == 'W')
		{
			col -= 1;
			tf = is_path(maze, row, col);
			if(tf == true)
			{
				maze->maze_array[row][col] = '.';
				counter++;
				
			}

		}
		step++;
	}

	//writes to visited file, closes, and frees memory
   	write_maze(visited_file, maze);

   	fclose(directions);
   	free_maze(maze);
	
	return counter;
}





