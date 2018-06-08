CC=mpicc
CFLAGS= -Wall -std=c99

compile_all:	
	compile_mpi_hello compile_mpi_hello2 compile_mpi_runvec compile_mpi_sumvec compile_mpi_minvec compile_mpi_sumvec_reduce compile_mpi_monte_carlo compile_mpi_montecarlo_reduce compile_montecarlo compile_mpi_master_slave-busca

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

compile_mpi_sumvec_reduce: mpi_sum_reduce.c
	${CC} ${CFLAGS} -o mpi_sum_reduce mpi_sum_reduce.c


compile_montecarlo: monte_carlo.c
	gcc -Wall -std=c99 -o monte_carlo monte_carlo.c

compile_mpi_monte_carlo: mpi_monte_carlo.c
	${CC} ${CFLAGS} -o mpi_monte_carlo mpi_monte_carlo.c

compile_mpi_montecarlo_reduce: mpi_montecarlo_reduce.c
	${CC} ${CFLAGS} -o mpi_montecarlo_reduce mpi_montecarlo_reduce.c

compile_mpi_master_slave-busca: mpi_master_slave-busca.c
	${CC} ${CFLAGS} -o mpi_master_slave-busca mpi_master_slave-busca.c

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

execute_mpi_sumvec_reduce:	
	mpirun -np 4 mpi_sum_reduce

execute_monte_carlo:
	./monte_carlo 100000000

execute_mpi_monte_carlo:
	mpirun -np 4 mpi_monte_carlo 100000000

execute_mpi_montecarlo_reduce:
	mpirun -np 4 mpi_montecarlo_reduce 100000000

execute_mpi_master_slave-busca:
	mpirun -np 4 mpi_master_slave-busca 100 10 1000000000

clear:
	rm -rf mpi_hello mpi_hello2 mpi_run_vect mpi_sum_vect mpi_min_vect mpi_sum_reduce mpi_monte_carlo mpi_montecarlo_reduce monte_carlo mpi_master_slave-busca






