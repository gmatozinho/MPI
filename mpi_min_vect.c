#include <mpi.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#define TAM_VET 12


/* Preciso entender para fazer */
int main(int argc, char *argv[])
{
    int size, rank;
    int global_min = -1;
    int vetor_rcv[TAM_VET / 2];
    int min_local[1];

    MPI_Init(&argc, &argv);

    MPI_Comm_rank(MPI_COMM_WORLD,&rank);
    MPI_Comm_size(MPI_COMM_WORLD,&size);

    if(rank==0)
    {
        srand(time(NULL));   // should only be called once
        int vetor_snd[TAM_VET];

        printf("Ola sou o processo 0\n");

        int part = TAM_VET / size;
        int pos_vetor;

        for(int i = 0;i<12;i++)
        {
            int r = rand() % 100;
            vetor_snd[i] = r;
            //printf("Rank %d de um total de %d\n", rank,size);
        }

        for (int rank_i = 0; rank_i < size; rank_i++)
        {
            pos_vetor = rank_i * part;
            printf("SEND %d\t%d\t%d\n", rank_i, part, pos_vetor);
            MPI_Send(&vetor_snd[pos_vetor], part, MPI_INT, rank_i, 123, MPI_COMM_WORLD);
        }      

        //printf("Rank %d de um total de %d\n", rank,size);
    }

    int part = TAM_VET / size;
    
    MPI_Recv(vetor_rcv, part, MPI_INT, 0, 123, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    int min = vetor_rcv[0] * 0.9;
    for (int i = 1; i < part; i++)
    {
        int multiply = vetor_rcv[i] * 0.9;
        if ( multiply < min ) 
        {
           min = multiply;
        }

        /* if(global_min == -1)
        {
            global_min == min;
        }else{
            if ( min < global_min ) 
            {
                global_min = min;
            }
        } */
    }

    printf("Rank %d\t%d\n", rank, min);

    MPI_Send(&min, 1, MPI_INT, 0, 124, MPI_COMM_WORLD);
    
    /* if(rank==0)
    {
        int sum = 0;
        for (int rank_i = 0; rank_i < size; rank_i++)
        {
            MPI_Recv(sum_ind, 1, MPI_INT, rank_i, 124, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            sum+=sum_ind[0];
        }

        printf("Resultado %d\n", sum);
    } */

    MPI_Finalize();
    return(0);
}