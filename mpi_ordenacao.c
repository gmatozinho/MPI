#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <mpi.h>

void merge(int *, int *, int, int, int);
void mergeSort(int *, int *, int, int);

int main(int argc, char** argv) {
	
	/* Start array */
	int n = 100;
	int original_array[n];
	
	int c;
	srand(time(NULL));
	printf("Vetor desordenado: ");
	for(c = 0; c < n; c++) {
		
		original_array[c] = rand() % n;
		printf("%d ", original_array[c]);
		
    }

	printf("\n");
	printf("\n");
	
	/*Init MPI*/
	int world_rank;
	int world_size;
	
    MPI_Init(NULL, NULL);
	MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
	MPI_Comm_size(MPI_COMM_WORLD, &world_size);
		
    /* Divide */
	int size = n/world_size;	
	int sub_array[size];
	MPI_Scatter(original_array, size, MPI_INT, sub_array, size, MPI_INT, 0, MPI_COMM_WORLD);
	
	/* Sort */
	int tmp_array[size];
	mergeSort(sub_array, tmp_array, 0, (size - 1));
	
	/* Get sorted*/
	int *sorted = NULL;
	if(world_rank == 0) {		
		sorted = malloc(n * sizeof(int));		
    }
	
	MPI_Gather(sub_array, size, MPI_INT, sorted, size, MPI_INT, 0, MPI_COMM_WORLD);
	
	/* Make final sort */
	if(world_rank == 0) {		
        int other_array[n];
		mergeSort(sorted, other_array, 0, (n - 1));
		
		printf("Vetor Ordenado: ");
		for(c = 0; c < n; c++) {			
			printf("%d ", sorted[c]);			
        }
			
		printf("\n");
		printf("\n");
			
		free(sorted);			
    }
	
	/********** Finalize MPI **********/
	MPI_Barrier(MPI_COMM_WORLD);
	MPI_Finalize();
	
}

/********** Merge Function **********/
void merge(int *vector_1, int *vector_2, int init, int average, int end) {
	
	int h, i, j, k;
	h = init;
	i = init;
	j = average + 1;
	
	while((h <= average) && (j <= end)) {
		
		if(vector_1[h] <= vector_1[j]) {
			
			vector_2[i] = vector_1[h];
			h++;			
        }
			
		else {			
			vector_2[i] = vector_1[j];
			j++;			
        }
			
		i++;		
    }
		
	if(average < h) {		
		for(k = j; k <= end; k++) {
			
			vector_2[i] = vector_1[k];
			i++;			
        }			
    }
		
	else {		
		for(k = h; k <= average; k++) {
			
			vector_2[i] = vector_1[k];
			i++;			
        }			
    }
		
	for(k = init; k <= end; k++) {		
		vector_1[k] = vector_2[k];		
    }
		
}

/********** Recursive Merge Function **********/
void mergeSort(int *vect_1, int *vect2, int init, int end) {
	
	int average;
	
	if(init < end) {		
		average = (init + end)/2;
		
		mergeSort(vect_1, vect2, init, average);
		mergeSort(vect_1, vect2, (average + 1), end);
		merge(vect_1, vect2, init, average, end);
		
    }
		
}