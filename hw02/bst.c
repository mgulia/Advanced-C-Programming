#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct _Tnode {
	   int info;
	      struct _Tnode *left;
		     struct _Tnode *right;
} Tnode;

typedef struct _Lnode {
	   Tnode *tree;
	      struct _Lnode *next;
} Lnode;

Lnode *Lnode_construct(Tnode *root)
{
	   Lnode *lnode = malloc(sizeof(*lnode));
	      if (lnode == NULL) {
			        fprintf(stderr, "can't allocate memory\n");
					      return NULL;
						     }
		     lnode->tree = root;
			    lnode->next = NULL;
				   return lnode;
}

Lnode *push(Lnode **stack, Tnode *root)
{
	   Lnode *lnode = Lnode_construct(root);
	      if (lnode == NULL) {
			        return NULL;
					   }
		     lnode->next = *stack;
			    *stack = lnode;
				   return lnode;
}

Lnode *pop(Lnode **stack)
{
	   Lnode *retlnode = *stack;
	      if (retlnode != NULL) {
			        *stack = retlnode->next;
					      retlnode->next = NULL;
						     }
		     return retlnode;
}   

int peek(Lnode *stack)
{
	   if (stack == NULL) {
		         return INT_MIN;
				    }
	      return stack->tree->info;
}

Tnode *Tnode_construct(int info)
{
	   Tnode *tnode = malloc(sizeof(*tnode));
	      if (tnode == NULL) {
			        fprintf(stderr, "can't allocate memory\n");
					      return NULL;
						     }
		     tnode->info = info;
			    tnode->left = tnode->right = NULL;
				   return tnode;
}

Tnode *construct_from_postorder(int *array, int lb, int ub)
{
	if (ub < lb)
	{
		return NULL;
	}

	Tnode *new_node = (Tnode *)(malloc(sizeof(Tnode)));
	
	new_node->info = array[ub];
	int median_index = ub - 1;
	
	while (median_index >= lb && array[median_index] > array[ub])
	{
		median_index--;
	}

	new_node->left = construct_from_postorder(array, lb, median_index);
	new_node->right = construct_from_postorder(array, median_index+1, ub-1);
	return new_node;

}

Tnode *BST_from_sorted_array(int *array, int lb, int ub)
{
	   if (lb > ub) {
		         return NULL;
				    }
	      int median_index = (lb + ub) / 2; // integer division
		     Tnode *root = Tnode_construct(array[median_index]);
			    if (root == NULL) {
					      return NULL;
						     }
				   root->left = BST_from_sorted_array(array, lb, median_index - 1);
				      root->right = BST_from_sorted_array(array, median_index + 1, ub);
					     return root;
}

int partition_array(int *array, int lb, int ub)
{
	   int pivot = array[lb];
	      int down = lb;
		     int up = ub;
			    while (down < up) { // as long as the indices have not crossed over
					      while (array[down] <= pivot && down < ub) {  // as long as we have elements less than or equal to pivot
							           down++;
									         } // encounter something that should go to the right
						        while (array[up] > pivot) { // as long as we have elements greater than pivot
									         up--;
											       }  // encounter something that should go to the left
								      if (down < up) { // exchange only if the indices have not crossed over
										           int tmp = array[down];
												            array[down] = array[up];
															         array[up] = tmp;
																	       }
									     }
				   array[lb] = array[up];
				      array[up] = pivot;
					     return up;
}

Tnode *BST_quick_sort(int *array, int lb, int ub)
{
	if (lb > ub) {
		      return NULL;
			     }
	   if (lb == ub) {
		         return Tnode_construct(array[lb]);
				    }
	      int partition_idx = partition_array(array, lb, ub);
		     Tnode *root = Tnode_construct(array[partition_idx]);
			    if (root == NULL) {
					      return NULL;
						     }
				   root->left = BST_quick_sort(array, lb, partition_idx - 1); 
				      root->right = BST_quick_sort(array, partition_idx + 1, ub); 
					     return root;
}

void inorder(Tnode *root)
{
	   if (root == NULL) 
		         return;
	      inorder(root->left);
		     fprintf(stdout, "%d ", root->info);
			    inorder(root->right);
}

void postorder(Tnode *root)
{
	   if (root == NULL) 
		         return;
	      postorder(root->left);
		     postorder(root->right);
			    fprintf(stdout, "%d ", root->info);
}

int postorder_collect(Tnode *root, int *array, int index)
{
	   if (root == NULL) {
		         return index;
				    }
	      index = postorder_collect(root->left, array, index);
		     index = postorder_collect(root->right, array, index);
			    array[index] = root->info;
				   return index+1;
}

void Tnode_destroy(Tnode *root)
{
	   if (root == NULL) {
		         return;
				    }
	      Tnode_destroy(root->left);
		     Tnode_destroy(root->right);
			    free(root);
}

void Lnode_destroy(Lnode *stack)
{
	   while (stack != NULL) {
		         Lnode *tmp = stack->next;
				       Tnode_destroy(stack->tree);
					         free(stack);
							       stack = tmp;
								      }
}


int main(int argc, char **argv)
{
	   int array[] = {0, 2, 4, 6, 8, 10, 12, 14, 16, 18, 20};
	      Tnode *root = BST_from_sorted_array(array, 0, sizeof(array)/sizeof(array[0]) - 1);
		     inorder(root);
			 	printf("\nIn order");
			    fputc('\n', stdout);
				   postorder(root);
				   printf("\nPost order");
				      fputc('\n', stdout);

					     Tnode_destroy(root);

						    int array2[] = {7, 8, 4, 10, 5, 9, 2, 3, 1, 6, 0};
							   Tnode *root2 = BST_quick_sort(array2, 0, sizeof(array2)/sizeof(array2[0]) - 1);
							      inorder(root2);
								  printf("\n In order root 2");
								     fputc('\n', stdout);
									    postorder(root2);
										printf("\n Post order root 2");
										   fputc('\n', stdout);

										      int *array3 = malloc(sizeof(*array3)*(sizeof(array2)/sizeof(array2[0])));
	int index = postorder_collect(root2, array3, 0);
	for (int i = 0; i < index; i++) {
	         fprintf(stdout, "%d ", array3[i]);
			    }
      fputc('\n', stdout);

   printf("\nPost order collect");
	     Tnode_destroy(root2);

Lnode *stack = NULL;
			   root = Tnode_construct(array3[0]);
			      push(&stack, root);
		    for (int i = 1; i < index; i++) {
				      root = Tnode_construct(array3[i]);
					        if (array3[i] < peek(stack)) {
								         Lnode *rnode = pop(&stack);
										          Lnode *lnode = pop(&stack);
												           root->left = lnode->tree;
														            root->right = rnode->tree;
																	         free(lnode);
																			          free(rnode);
																					        }
							      push(&stack, root);
								     }
			   inorder(stack->tree);
			   printf("\nIn order stack tree");
			      fputc('\n', stdout);
				     postorder(stack->tree);
					 printf("\nPost order stack tree");
					    fputc('\n', stdout);
						   Lnode_destroy(stack);
						      free(array3);

							  int arr[] = {10, 30, 40, 20, 60, 80, 70, 110, 120, 100, 90, 50};
							  Tnode *bst = construct_from_postorder(arr, 0, 11);
							


							     return EXIT_SUCCESS;
}









