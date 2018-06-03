// Program that computes the average of an array of elements in parallel using
// MPI_Reduce.
//
#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include <assert.h>
#include <time.h>

int main(int argc, char** argv) {

    MPI_Init(NULL, NULL);

    int vector[] = {10, 20, 30, 40, 50, 60, 70, 80, 90, 100, 110, 120};
    int world_rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
    int world_size;
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);
    // Sum the numbers locally
    int local_sum = 0;
    int part = 12/world_size;
    int init = part * world_rank;
    int i;
    for (i = init; i < (init+part); i++) {
        local_sum += vector[i];
    }

    // Print the random numbers on each process
    printf("Local sum for process %d - %d\n",
            world_rank, local_sum);

    // Reduce all of the local sums into the global sum
    int global_sum;
    MPI_Reduce(&local_sum, &global_sum, 1, MPI_FLOAT, MPI_SUM, 0,
                MPI_COMM_WORLD);

    // Print the result
    if (world_rank == 0) {
        printf("Total sum = %d\n", global_sum);
    }

    MPI_Barrier(MPI_COMM_WORLD);
    MPI_Finalize();
}