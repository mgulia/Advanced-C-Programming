

#include <stdio.h>
#include <stdlib.h>


//int array[] = {7, 8, 4, 9, 5, 10, 2, 3, 1, 6, 0};
//int globe = sizeof(array)/sizeof(array[0]);

void print_array(int *array, int nmemb)
{
	for (int i = 0; i < nmemb; i++) {
		         fprintf(stdout, "%d ", array[i]);
				    }
	      fprintf(stdout, "\n");
}

	

int partition_array(int *array, int lb, int ub)
{
	int pivot = array[lb];
	int down = lb;
	int up = ub;
	while (down < up){
		while (array[down] <= pivot && down < ub){
			down++;
		}
		while (array[up] > pivot){
			up--;
		}
		if (down < up){
			int tmp = array[down];
			array[down] = array[up];
			array[up] = tmp;
		}
	}

	array [lb] = array[up];
	array[up] = pivot;

	return up;
}
void quick_sort(int *array, int lb, int ub, int nmemb)
{
	if (lb>=ub){
		return;
	}

	int partition_idx = partition_array(array, lb, ub);
	quick_sort(array, lb, partition_idx - 1, nmemb);
	quick_sort(array, partition_idx + 1, ub, nmemb);
	print_array(array, nmemb);
	
	printf("Parition is %d \n", partition_idx);

}


int main(int argc, char* argv[])
{
	int array[] = {7, 8, 4, 9, 5, 10, 2, 3, 1, 6, 0};
	
//	int array[] = {0, 1, 2, 3};
//	int array[] = {3, 5, 6, 1};
	
//	int array[] = {10, 9, 8};

	int nmemb = sizeof(array)/sizeof(array[0]);
   	print_array(array, nmemb);
    quick_sort(array, 0, nmemb-1, nmemb);
	print_array(array, nmemb);

	return (EXIT_SUCCESS);

}

















