#include <mpi.h>
#include <stdio.h>
#include <string.h>

/* Compilar:
    mpicc mpi_hello2.c -o mpi_hello2 -Wall
Executar:
    mpirun -np 4 mpi_hello2 */

int main(int argc, char *argv[])
{
    int size, rank;
    char vector[100];

    MPI_Init(&argc, &argv);

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    printf("Rank %d de um total de %d\n", rank, size);

    if(rank==0)
    {
        strcpy(vector,"Ola, eu sou o processo 0\n");
        
        for(int i = 1; i < size; i++)
        {
            /* code */
            MPI_Send(&vector, 100, MPI_CHAR, i, 123, MPI_COMM_WORLD);
        }
        
    }else{
        MPI_Recv(vector,100,MPI_CHAR,0,123,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
        printf("Rank %d:%s\n",rank,vector);
    }


    MPI_Finalize();
    return (0);
}
