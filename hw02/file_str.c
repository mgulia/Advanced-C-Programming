#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _StrArray {
	   char **str_array;
	      int n_str;
} StrArray;

void Free_memory(int n_str, char **str_arr)
{
	   for (int i = 0; i < n_str; i++) {
		         free(str_arr[i]);
				    }
	      free(str_arr);
}

StrArray *Read_from_file(char *filename)
{
	   FILE *fp = fopen(filename, "r");
	      if (fp == NULL) {
			        fprintf(stderr, "can't open file\n");
					      return NULL;
						     }
		     int n_str = 0;
			    for (int c = fgetc(fp); c != EOF; c = fgetc(fp)) {
					      if (c == '\n') {
							           n_str++;
									         }
						     }
				   char **str_array = malloc(sizeof(*str_array) * n_str);
				      if (str_array == NULL) {
						        fprintf(stderr, "can't get memory\n");
								      fclose(fp);
									        return NULL;
											   }
					  long begin_pos = ftell(fp); 
					     n_str = 0;
						    int c_while;
							   while ((c_while = fgetc(fp)) != EOF) {
								         if (c_while == '\n') {
											          long end_pos = ftell(fp);
													           int string_len = end_pos - begin_pos;
									str_array[n_str] = malloc(sizeof(*(str_array[n_str])) * string_len);
									         if (str_array[n_str] == NULL) {
												             Free_memory(n_str, str_array);
															             fclose(fp);
																		             return NULL;
																					          }
											 fseek(fp, begin_pos, SEEK_SET); 
											 int count = 0;
											          int c_char;
													           while ((c_char = fgetc(fp)) != '\n') {
																               str_array[n_str][count] = c_char;
																			               count++;
																						            }
															            str_array[n_str][count] = '\0';
											begin_pos = end_pos;
											         n_str++;
													       }
										    }
							   fseek(fp, 0L, SEEK_SET);
							      int count = 0;
								     for (int i = 0; i < n_str;)  {
										       int c = fgetc(fp);
											         if (c == '\n') {
														          str_array[i][count] = '\0';
																           count = 0;
																		            i++;
																					      } else {
																							           str_array[i][count] = c;
																									            count++;
																												      }
													    }
									    fclose(fp);
										   StrArray *strarr = malloc(sizeof(*strarr));
										      if (strarr == NULL) {
												        Free_memory(n_str, str_array);
														      return NULL;
															     }
											     strarr->n_str = n_str;
												    strarr->str_array = str_array;
													   return strarr;
}


void Free_str_array(StrArray *str_arr)
{
	   if (str_arr) {
		         Free_memory(str_arr->n_str, str_arr->str_array);
				    }
	      free(str_arr);
}

int main(int argc, char **argv)
{
	   if (argc != 2) {
		         fprintf(stderr, "expect a filename\n");
				       return EXIT_FAILURE;
					      }
	      StrArray *strarr = Read_from_file(argv[1]);
		     if (strarr == NULL) {
				       fprintf(stderr, "can't read properly\n");
					         return EXIT_FAILURE;
							    }
			    for (int i = 0; i < strarr->n_str; i++) {
					      fprintf(stdout, "%s\n", strarr->str_array[i]);
						     }
				   Free_str_array(strarr);
				      return EXIT_SUCCESS;
}
























