#include <mpi.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include <stdlib.h>

int sum_pos(int init,int part)
{
    double x,y;
    int circle_count = 0;
    int end = init + part;

    for (int i = init; i < end; i++)
    {
        x = ((double)rand() / (RAND_MAX)) * 2.0 -1.0;
        y = ((double)rand() / (RAND_MAX)) * 2.0 - 1.0;

        if((x*x) + (y*y) <= (1*1))
        {
            circle_count += 1;
        } 
    }

    return circle_count;
}

int main(int argc, char *argv[])
{

    int size, rank;

    int npoints = 10000;//atoi(argv[2]);

    srand(time(NULL));

    MPI_Init(&argc, &argv);

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int part = npoints/size;

    if(rank == 0)
    {
        int sum_ind;
        int sum = sum_pos(0, part);
        printf("Resultado de 0 foi %d\n", sum);

        for (int rank_i = 1; rank_i < size; rank_i++)
        {
            MPI_Recv(&sum_ind, 1, MPI_INT, rank_i, 124, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            sum += sum_ind;
        }

        double result = (double) sum/part;
        printf("Resultado %f\n", result);
    }
    else{
        int init = rank * part;
        int sum = sum_pos(init, part);
        printf("Resultado de %d foi %d\n",rank, sum);
        MPI_Send(&sum, 1, MPI_INT, 0, 124, MPI_COMM_WORLD);
    }

    MPI_Finalize();
    return 0;
}
