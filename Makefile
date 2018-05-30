CC=mpicc
CFLAGS= -Wall -std=c99

compile_all:	compile_mpi_hello compile_mpi_hello2 compile_mpi_runvec compile_mpi_sumvec

compile_mpi_hello: mpi_hello.c
	${CC} ${CFLAGS}  -o mpi_hello mpi_hello.c

compile_mpi_hello2: mpi_hello2.c
	${CC} ${CFLAGS} -o mpi_hello2 mpi_hello2.c

compile_mpi_runvec: mpi_run_vect.c
	${CC} ${CFLAGS} -o mpi_run_vect mpi_run_vect.c
	
compile_mpi_sumvec: mpi_sum_vect.c
	${CC} ${CFLAGS} -o mpi_sum_vect mpi_sum_vect.c

compile_mpi_minvec: mpi_min_vect.c
	${CC} ${CFLAGS} -o mpi_min_vect mpi_min_vect.c


compile_monte_carlo: mpi_monte_carlo.c
	${CC} ${CFLAGS} -o mpi_monte_carlo mpi_monte_carlo.c

execute_mpi_hello:
	mpirun -np 4 mpi_hello

execute_mpi_hello2:
	mpirun -np 4 mpi_hello2

execute_run_vect:	
	mpirun -np 4 mpi_run_vect

execute_sum_vect:	
	mpirun -np 4 mpi_sum_vect

execute_min_vect:	
	mpirun -np 4 mpi_min_vect

execute_monte_carlo:
	mpirun -np 4 mpi_monte_carlo

clear:
	rm -rf mpi_hello mpi_hello2 mpi_run_vect mpi_sum_vect mpi_min_vect mpi_monte_carlo






