#include <stdio.h>
#include <stdlib.h>

typedef struct _Node {
	   int info;
	      struct _Node *next;
} Node;


Node *node_constructor(int info)
{
	   Node *node = malloc(sizeof(Node));
	      if (node == NULL) {
			        fprintf(stderr, "can't get memory for Node\n");
					      return NULL;
						     }
		     node->info = info;
			    node->next = NULL;
				   return node;
}

Node *search_and_remove_from_ordered_list(Node **header, int s_key)
{
	   if (*header == NULL) {
		         return NULL;
				    }

	   Node dummy;
	      dummy.next = *header;

		     Node *prev = &dummy;
			    Node *curr = *header;

				   while (curr != NULL) {
					         if (curr->info == s_key) {
								          break;
										        }
							       if (curr->info > s_key) {
									            curr = NULL;
												         break;
														       }
								         prev = curr;
										       curr = curr->next;
											      }
				      if (curr != NULL) {
						        prev->next = curr->next;
								      curr->next = NULL;
									     }
					     *header = dummy.next;
						    return curr;
}


Node *insert_in_order(Node **header, int info)
{
	   Node *new_node = node_constructor(info);
	      if (new_node == NULL) {
			        return NULL;
					   }
		     Node dummy;
			    // dummy.next pointing at the first item of the list
				    dummy.next = *header;
					 Node *prev = &dummy;
					    Node *curr = *header;
						   while (curr != NULL) {
							   if (curr->info >= info) {
								            break;
											      }
							         prev = curr;
									       curr = curr->next;
										      }
						    
						      prev->next = new_node;
							     new_node->next = curr;

								    *header = dummy.next;
									   return new_node;
}

Node *insert_in_front(Node **header, int info)
{
	   Node *new_node = node_constructor(info);
	      if (new_node == NULL) {
			        return NULL;
					   }
		     new_node->next = *header;
			    *header = new_node;
				   return new_node;
}

Node *remove_from_front(Node **header)
{
	   if (*header == NULL) {
		         return NULL;
				    }
	      Node *ret_node = *header;
		     *header = ret_node->next;
			    ret_node->next = NULL;
				   return ret_node;
}

void print_list(Node *header)
{
	   Node *curr = header;
	      while (curr != NULL) {
			        fprintf(stdout, "%d ", curr->info);
					      curr = curr->next;
						     }
		     fputc('\n', stdout);
}

void recursive_list_destroy(Node *header)
{
	   if (header == NULL) {
		         return;
				    }
	      recursive_list_destroy(header->next);
		     free(header);
}

void list_destroy(Node *header)
{
	   Node *curr = header;
	      while (curr != NULL) {
			        Node *tmp = curr->next;
					      free(curr);
						        curr = tmp;
								   }
}

int main(int argc, char **argv)
{
	   FILE *ifp;
	      if (argc < 2) {
			        fprintf(stderr, "read from stdin\n");
					      ifp = stdin;
						     } else {
								       fprintf(stderr, "read from file argv[1]\n");
									         ifp = fopen(argv[1], "r");
											       if (ifp == NULL) {
													            fprintf(stderr, "can't open file argv[1]\n");
																         fprintf(stderr, "read from stdin\n");
																		          ifp = stdin;
																				        }
												      }
		     Node *header = NULL; // initialize an empty list
			    
			    int read_number;
				   while (fscanf(ifp, "%d", &read_number) > 0) {
					         Node *node = insert_in_front(&header, read_number);
							       if (node == NULL) {
									            fprintf(stderr, "can't get memory, no change to list\n");
												      }
								         print_list(header);
										    }
				      if (ifp != stdin) {
						        fclose(ifp);
								   }

					     FILE *ofp;

						    if (argc >= 3) {
								      ofp = fopen(argv[2], "w");
									        if (ofp == NULL) {
												         fprintf(stderr, "can't open file argv[2]\n");
														          fprintf(stderr, "write to stdout\n");
																           ofp = stdout;
																		         }
											   } else {
												         fprintf(stderr, "write to stdout\n");
														       ofp = stdout;
															      }

							   Node *curr = header;
							      while (curr != NULL) {
									        fprintf(ofp, "%d ", curr->info); 
											      curr = curr->next;
												     }
								     fputc('\n', ofp);

									    if (ofp != stdout) {
											      fclose(ofp);
												     }
										   list_destroy(header);
										      header = NULL;  // if you need header again

											     return EXIT_SUCCESS;
}
