/****************************************************************************/
/*                                                                          */
/* Nome: Sergio Nery Simoes                                                 */
/* Exercicio: Modelo Master/Slave em MPI                                    */
/* Descricao: Implementacao do modelo master/slave em MPI                   */
/*            para buscar um dado elemento em um matriz.                    */
/*            Assim que o elemento for encontrado o programa finalizara     */
/*                                                                          */
/* Compilar: mpicc mpi_master_slave.c -o mpi_master_slave -Wall */
/* Executar: mpirun -np 2 mpi_master_slave <elem> <tam_bl> <tam_vet>   */
/* Exemplos:                                                                */
/*           time mpirun -np 3 mpi_master_slave 9 5 1000000           */
/*           time mpirun -np 3 mpi_master_slave 987654 5 1000000      */
/*                                                                          */
/****************************************************************************/

#include <stdlib.h>
#include <stdio.h>
#include <mpi.h>
#include <math.h>

#define TAG_ELEM   0
#define TAG_WORK   1
#define TAG_RESULT 2
#define TAG_END    3

#define FALSE 0
#define TRUE  1

void master(nprocs, elem, block_size, v_in_size, v_in, found)
	int nprocs, block_size, v_in_size, *found;
	double elem, *v_in;
{
	int result, rank_i, v_in_pos = 0,process_used=0;
	MPI_Status status;
	found[0] = FALSE;

	if(nprocs==1)
	{
		printf("we do not have slaves\n");
		return;
	}

	//printf("0-master sends <elem=%lf> to all slaves\n", elem);
	for (rank_i=1; rank_i<nprocs; rank_i++){
		MPI_Send(&elem, 1, MPI_DOUBLE, rank_i, TAG_ELEM, MPI_COMM_WORLD);
	}
	//printf("1-master sends 1 work to all slaves\n");
	for (rank_i=1; rank_i<nprocs && v_in_pos<v_in_size; rank_i++)
	{
		MPI_Send(&v_in[v_in_pos], block_size, MPI_DOUBLE, rank_i, TAG_WORK, MPI_COMM_WORLD);
		v_in_pos += block_size;
		process_used++;
	}
	//printf("2-master receive results from slaves and sends new works until works ends\n");
	while (v_in_pos<v_in_size && !(found[0]))
	{
		MPI_Recv(&result, 1, MPI_INT, MPI_ANY_SOURCE, TAG_RESULT, MPI_COMM_WORLD, &status);
		found[0] = found[0] || result;
		MPI_Send(&v_in[v_in_pos], block_size, MPI_DOUBLE, status.MPI_SOURCE, TAG_WORK, MPI_COMM_WORLD);
		v_in_pos  += block_size;
	}

	if(found[0]){
		found[1] = status.MPI_SOURCE;
	}

	//printf("3-master receives last results from all slaves\n");
	for (rank_i=1; rank_i<=process_used; rank_i++)
	{
		MPI_Recv(&result, 1, MPI_INT, MPI_ANY_SOURCE, TAG_RESULT, MPI_COMM_WORLD, &status);
		found[0] = found[0] || result;
	}

	if(found[0]){
		if(found[1]==-1)
		{
			found[1] = status.MPI_SOURCE;
		}
	}
	
	//printf("4-master sends termination TAG\n");
	for (rank_i=1; rank_i<nprocs; rank_i++)
		MPI_Send(NULL, 0, MPI_DOUBLE, rank_i, TAG_END, MPI_COMM_WORLD);
}

void slaves_function(double elem, int v_in_size, double *v_in, int *found)
{
	int i;
	*found = FALSE;
	for (i=0; i<v_in_size && !(*found); i++)
			*found = (v_in[i]==elem);
}

int slave(int v_in_size, double *v_in)
{
	double elem;
	int result[1];
	MPI_Status status;
	MPI_Recv(&elem, 1, MPI_DOUBLE, 0, TAG_ELEM, MPI_COMM_WORLD, &status);
	for (;;)
	{
		MPI_Recv(v_in, v_in_size, MPI_DOUBLE, 0, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
		if (status.MPI_TAG==TAG_END)
			break;
		slaves_function(elem, v_in_size, v_in, &result[0]);
		MPI_Send(result, 1, MPI_INT, 0, TAG_RESULT, MPI_COMM_WORLD);
	}
	return 0;
}


void init_vector(int v_size, double *v)
{
	int i;
	for (i=0; i<v_size; i++)
	{
		v[i] = i;
	}
}

void print_vector(int v_size, double *v)
{
	int i;
	for (i=0; i<v_size; i++)
		printf("v[%d]=%-8.2lf\t", i, v[i]);
	printf("\n");
}

void program_finalize(int error_code)
{
	MPI_Finalize();
	exit(error_code);
}
void read_arguments(int argc, char **argv, double *elem, int *block_size, int *v_in_size)
{
	if (argc==4)
	{
		*elem       = atoi(argv[1]);
		*block_size = atoi(argv[2]);
		*v_in_size  = atoi(argv[3]);
		if ((*v_in_size % *block_size)!=0)
		{
			printf("<vector_size> must be multiple of <block_size>\n");
			program_finalize(-2);
		}
	}
	else
	{
		printf("Usage: %s <elem> <block_size> <vector_size>\n\n", argv[0]);
		program_finalize(-1);
	}
}

int main(int argc, char *argv[])
{
	int /* found, */ rank, nprocs, block_size, v_in_size=100;
	double elem, *v_in;
	int found[] = {-1,-1};

	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &nprocs);
	read_arguments(argc, argv, &elem, &block_size, &v_in_size);
	if (rank == 0)
	{
		v_in  = (double*) calloc(v_in_size, sizeof(double));
		init_vector(v_in_size, v_in);
		//print_vector(v_in_size, v_in);
		master(nprocs, elem, block_size, v_in_size, v_in, &found);
		if(found[0])
		{
			printf("Found by Rank:%d\n", found[1]);
		}else{
			printf("Not found\n");
		}
		
		free(v_in);
	}
	else
	{
		v_in_size  = block_size;
		v_in  = (double*) calloc(v_in_size, sizeof(double));
		slave(v_in_size, v_in);
		free(v_in);
	}	
	MPI_Finalize();
	return 0;
}

