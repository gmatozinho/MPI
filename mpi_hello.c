#include <mpi.h>
#include <stdio.h>


/* Compilar:
    mpicc mpi_hello.c -o mpi_hello -Wall
Executar:
    mpirun -np 4 mpi_hello */
    
int main(int argc, char *argv[])
{
    int size, rank;

    MPI_Init(&argc, &argv);

    MPI_Comm_rank(MPI_COMM_WORLD,&rank);
    MPI_Comm_size(MPI_COMM_WORLD,&size);

    printf("Rank %d de um total de %d\n", rank,size);

    MPI_Finalize();
    return(0);
}

