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
	   int array[] = {10, -1, 5, 23, 264, 7};
	      
	      Node *header = NULL; // initialize an empty list
		     for (int i = 0; i < sizeof(array)/sizeof(array[0]); i++) {
				       Node *node = insert_in_front(&header, array[i]);
					         if (node == NULL) {
								          fprintf(stderr, "can't get memory, no change to list\n");
										        }
							       print_list(header);
								      }
			
			 printf("\nNew Stuff\n");

			    Node *rem_node = remove_from_front(&header);
				   while (rem_node != NULL) {
					         fprintf(stdout, "%d\n", rem_node->info);
							       free(rem_node);
								         rem_node = remove_from_front(&header);
										    }

			
			 printf("\nNew Stuff\n");
				      for (int i = 0; i < sizeof(array)/sizeof(array[0]); i++) {
						        Node *node = insert_in_order(&header, array[i]);
								      if (node == NULL) {
										           fprintf(stderr, "can't get memory, no change to list\n");
												         }
									        print_list(header);
											   }

			
			 printf("\nNew Stuff\n");
					     int j = 0;
						    rem_node = search_and_remove_from_ordered_list(&header, array[j]);
							   while (rem_node != NULL) {
								         fprintf(stdout, "%d\n", rem_node->info);
										       free(rem_node);
											         j++;
													       rem_node = search_and_remove_from_ordered_list(&header, array[j]);
														      }
							      
			
			 printf("\nNew Stuff\n");
							      list_destroy(header);
								     header = NULL;  // if you need header again

									    return EXIT_SUCCESS;
}






























