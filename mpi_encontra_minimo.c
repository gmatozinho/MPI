// Program that computes the min of an array of elements in parallel using
// MPI_Reduce.
//
#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include <assert.h>
#include <time.h>

#define EPSILON 0.00009
#define SIZE_VECT 1000000

int main(int argc, char** argv) {

    MPI_Init(NULL, NULL);
    srand(time(NULL));
    float vector[SIZE_VECT];

    for(int i = 0;i<SIZE_VECT;i++)
    {
        float r = (rand() % 100)+1;
        vector[i] = r;
    }

    int world_rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
    int world_size;
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);
    // Sum the numbers locally
    float min_local = 10000;
    int interaction_local = 0;
    int part = SIZE_VECT/world_size;
    int init = part * world_rank;
    int i;
    float global_min;
    int interaction_sum;

    while(1)
    {
        for (i = init; i < (init+part); i++) {
            interaction_local += 1;
            vector[i] *= 0.9;

            if(vector[i] <= min_local)
            {
                min_local = vector[i];

                if(min_local <= EPSILON)
                {
                    break;
                }
            }
            
        }
        
        MPI_Allreduce(&min_local, &global_min, 1, MPI_FLOAT, MPI_MIN, MPI_COMM_WORLD);       
        
        if(global_min <= EPSILON)
        {
            break;
        }    
    }

    // Print the random numbers on each process
    printf("Local min for process %d - %f\n",
            world_rank, min_local);

    printf("Local interaction for process %d - %d\n",
            world_rank, interaction_local);

    MPI_Reduce(&interaction_local, &interaction_sum, 1, MPI_INT, MPI_SUM,0, MPI_COMM_WORLD);

    // Print the result
    if (world_rank == 0) {
        printf("Minimo global = %f, Interações = %d \n", global_min, interaction_sum);
    }

    MPI_Barrier(MPI_COMM_WORLD);
    MPI_Finalize();
}