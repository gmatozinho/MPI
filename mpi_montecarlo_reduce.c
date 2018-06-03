#include <mpi.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include <stdlib.h>

#define MASTER 0

int sum_circle_count(int part)
{
    double x,y;
    int circle_count = 0;

    for (int i = 0; i < part; i++)
    {
        x = ((double)rand() / (RAND_MAX)) * 2.0 -1.0;
        y = ((double)rand() / (RAND_MAX)) * 2.0 - 1.0;

        if((x*x) + (y*y) <= (1.0*1.0))
        {
            circle_count += 1;
        } 
    }

    return circle_count;
}

int main(int argc, char *argv[])
{
    if (argc != 2) {
        fprintf(stderr, "Usage: avg num_elements_per_proc\n");
        exit(1);
    }

    int size, rank, localCircleCount, circleCountsum;

    int npoints = atoi(argv[1]);;//atoi(argv[2]);

    srand(time(NULL));

    MPI_Init(&argc, &argv);

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int part = npoints/size;

    localCircleCount = sum_circle_count(part);
    MPI_Reduce(&localCircleCount, &circleCountsum, 1, MPI_INT, MPI_SUM, MASTER, MPI_COMM_WORLD);

    if(rank==MASTER)
    {
        double result = 4.0*circleCountsum/npoints;        
        printf("Resultado %f\n", result);
    }
    
    MPI_Finalize();
    return 0;
}
