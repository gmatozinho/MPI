CC=gcc 
CFLAGS=-Wall

compile_all:	compile_mpi_hello compile_mpi_hello2

compile_mpi_hello: mpi_hello.c
	mpicc -o mpi_hello mpi_hello.c

compile_mpi_hello2: mpi_hello2.c
	mpicc -o mpi_hello2 mpi_hello2.c

compile_mpi_sumvec: mpi_sum_vect.c
	mpicc -o mpi_sum_vect mpi_sum_vect.c
	
compile_mpi_sumvec_up: mpi_sum_vect_up.c
	mpicc -o mpi_sum_vect_up mpi_sum_vect_up.c

executar_1:
	mpirun -np 4 mpi_hello

executar_2:
	mpirun -np 4 mpi_hello2

executar_sumvec:	
	mpirun -np 4 mpi_sum_vect

executar_sumvec_up:	
	mpirun -np 4 mpi_sum_vect_up






