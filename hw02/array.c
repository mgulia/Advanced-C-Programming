#include <stdio.h>
#include <stdlib.h>

void print_a(int (*array3d)[6][3], int xdim);
void print_b(void *ptr, int xdim, int ydim, int zdim);

void Free_memory(int ***array3d, int xdim, int ydim)
{
	   if (array3d != NULL) {
		         for (int i = 0; i < xdim; i++) {
					          if (array3d[i] != NULL) {
								              for (int j = 0; j < ydim; j++) {
												                 free(array3d[i][j]);
																             }
											              free(array3d[i]);
														           }
							        }
				       free(array3d);
					      }
}

int main(int argc, char **argv)
{
	   if (argc != 4) {
		         fprintf(stderr, "expecting 3 arguments\n");
				       return EXIT_FAILURE;
					      }
	      int xdim, ydim, zdim;
		     char *end_str;
			    xdim = strtol(argv[1], &end_str, 10);
				   if (*end_str != '\0') {
					         fprintf(stderr, "expecting arguments to be integer\n");
							       return EXIT_FAILURE;
								      }
				      ydim = strtol(argv[2], &end_str, 10);
					     if (*end_str != '\0') {
							       fprintf(stderr, "expecting arguments to be integer\n");
								         return EXIT_FAILURE;
										    }
						    zdim = strtol(argv[3], &end_str, 10);
							   if (*end_str != '\0') {
								         fprintf(stderr, "expecting arguments to be integer\n");
										       return EXIT_FAILURE;
											      }

int ***array3d = calloc(xdim, sizeof(*array3d));
   if (array3d == NULL) {
	         fprintf(stderr, "not getting memory\n");
			       return EXIT_FAILURE;
				      }
      for (int i = 0; i < xdim; i++) {
		        array3d[i] = calloc(ydim, sizeof(*(array3d[i])));
				      if (array3d[i] == NULL) {
						           Free_memory(array3d, xdim, ydim);
								            fprintf(stderr, "not getting memory\n");
											         return EXIT_FAILURE;
													       }
					        for (int j = 0; j < ydim; j++) {
								         array3d[i][j] = malloc(sizeof(*(array3d[i][j])) * zdim);
										          if (array3d[i] == NULL) {
													              Free_memory(array3d, xdim, ydim);
																              fprintf(stderr, "not getting memory\n");
																			              return EXIT_FAILURE;
																						           }
												        }
							   }

	     for (int i = 0; i < xdim; i++) {
			       for (int j = 0; j < ydim; j++) {
					            for (int k = 0; k < zdim; k++) {
									            array3d[i][j][k] = j;
												         }
								      }
				      }
		    for (int i = 0; i < xdim; i++) {
				      for (int j = 0; j < ydim; j++) {
						           for (int k = 0; k < zdim; k++) {
									               fprintf(stdout, "%d ", array3d[i][j][k]);
												            }
								         }
					        fputc('\n', stdout);
							   }
			   

			   for (int i = 0; i < xdim; i++) {
				         for (int j = 0; j < ydim; j++) {
							          free(array3d[i][j]);
									        }
						       free(array3d[i]);
							      }
			      free(array3d);
int array3d_d[5][6][3];
   xdim = 5; 
      ydim = 6;
	     zdim = 3;
		    for (int i = 0; i < xdim; i++) {
				      for (int j = 0; j < ydim; j++) {
						           for (int k = 0; k < zdim; k++) {
									               array3d_d[i][j][k] = j;
												            }
								         }
					     }
			   print_a(&(array3d_d[0]), xdim);
		int array1d[] = {0, 0, 0, 1, 1, 1, 2, 2, 2, 3, 3, 3, 4, 4, 4, 5, 5, 5,
			                    0, 0, 0, 1, 1, 1, 2, 2, 2, 3, 3, 3, 4, 4, 4, 5, 5, 5,
								                    0, 0, 0, 1, 1, 1, 2, 2, 2, 3, 3, 3, 4, 4, 4, 5, 5, 5,
													                    0, 0, 0, 1, 1, 1, 2, 2, 2, 3, 3, 3, 4, 4, 4, 5, 5, 5,
																		                    0, 0, 0, 1, 1, 1, 2, 2, 2, 3, 3, 3, 4, 4, 4, 5, 5, 5};
		   print_a((int (*)[6][3])&(array1d[0]), xdim);

		      print_b(&(array1d[0]), ydim, zdim, xdim);
			     print_b(&(array1d[0]), xdim, ydim, zdim);
				    print_b(&(array1d[0]), zdim, ydim, xdim);
					   return EXIT_SUCCESS;
}

void print_a(int (*array3d)[6][3], int xdim)
{
	   for (int i = 0; i < xdim; i++) {
		         for (int j = 0; j < 6; j++) {
					          for (int k = 0; k < 3; k++) {
								              fprintf(stdout, "%d ", array3d[i][j][k]);
											           }
							        }
				       fputc('\n', stdout);
					      }
}

void print_b(void *ptr, int xdim, int ydim, int zdim)
{
	   int (*array3d)[ydim][zdim] = ptr;
	      for (int i = 0; i < xdim; i++) {
			        for (int j = 0; j < ydim; j++) {
						         for (int k = 0; k < zdim; k++) {
									             fprintf(stdout, "%d ", array3d[i][j][k]);
												          }
								       }
					      fputc('\n', stdout);
						     }
}


