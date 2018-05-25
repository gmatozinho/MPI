CC=mpicc
CFLAGS=-Wall -DMPI -std=gnu99

compile_all:	compile_mpi_hello compile_mpi_hello2 compile_mpi_runvec compile_mpi_sumvec

compile_mpi_hello: mpi_hello.c
	mpicc -o mpi_hello mpi_hello.c

compile_mpi_hello2: mpi_hello2.c
	mpicc -o mpi_hello2 mpi_hello2.c

compile_mpi_runvec: mpi_run_vect.c
	mpicc -o mpi_run_vect mpi_run_vect.c
	
compile_mpi_sumvec: mpi_sum_vect.c
	mpicc -o mpi_sum_vect mpi_sum_vect.c

execute_mpi_hello:
	mpirun -np 4 mpi_hello

execute_mpi_hello2:
	mpirun -np 4 mpi_hello2

execute_run_vect:	
	mpirun -np 4 mpi_run_vect

execute_sum_vect:	
	mpirun -np 4 mpi_sum_vect

clear:
	rm -rf mpi_hello mpi_hello2 mpi_run_vect mpi_sum_vect 






