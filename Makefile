CC=mpicc
CFLAGS= -Wall -std=c99

compile_all:	compile_mpi_hello compile_mpi_hello2 compile_mpi_runvec compile_mpi_sumvec compile_mpi_sumvec_reduce compile_mpi_monte_carlo compile_mpi_montecarlo_reduce compile_montecarlo compile_mpi_master_slave compile_mpi_encontra_minimo

compile_mpi_hello: mpi_hello.c
	${CC} ${CFLAGS}  -o mpi_hello mpi_hello.c

compile_mpi_hello2: mpi_hello2.c
	${CC} ${CFLAGS} -o mpi_hello2 mpi_hello2.c

compile_mpi_runvec: mpi_run_vect.c
	${CC} ${CFLAGS} -o mpi_run_vect mpi_run_vect.c
	
compile_mpi_sumvec: mpi_sum_vect.c
	${CC} ${CFLAGS} -o mpi_sum_vect mpi_sum_vect.c

compile_mpi_encontra_minimo: mpi_encontra_minimo.c
	${CC} ${CFLAGS} -o mpi_encontra_minimo mpi_encontra_minimo.c

compile_mpi_ordenacao: mpi_ordenacao.c
	${CC} ${CFLAGS} -o mpi_ordenacao mpi_ordenacao.c

compile_mpi_sumvec_reduce: mpi_sum_reduce.c
	${CC} ${CFLAGS} -o mpi_sum_reduce mpi_sum_reduce.c

compile_montecarlo: monte_carlo.c
	gcc -Wall -std=c99 -o monte_carlo monte_carlo.c

compile_mpi_monte_carlo: mpi_monte_carlo.c
	${CC} ${CFLAGS} -o mpi_monte_carlo mpi_monte_carlo.c

compile_mpi_montecarlo_reduce: mpi_montecarlo_reduce.c
	${CC} ${CFLAGS} -o mpi_montecarlo_reduce mpi_montecarlo_reduce.c

compile_mpi_master_slave: mpi_master_slave.c
	${CC} ${CFLAGS} -o mpi_master_slave mpi_master_slave.c

compile_mpi_master_slave_desviopadrao: mpi_master_slave_desviopadrao.c
	${CC} ${CFLAGS} -o mpi_master_slave_desviopadrao mpi_master_slave_desviopadrao.c

execute_mpi_hello:
	mpirun -np 4 mpi_hello

execute_mpi_hello2:
	mpirun -np 4 mpi_hello2

execute_run_vect:	
	mpirun -np 4 mpi_run_vect

execute_sum_vect:	
	mpirun -np 4 mpi_sum_vect

execute_mpi_encontra_minimo:	
	mpirun -np 4 mpi_encontra_minimo

execute_mpi_sumvec_reduce:	
	mpirun -np 4 mpi_sum_reduce

execute_mpi_ordenacao:	
	mpirun -np 4 mpi_ordenacao

execute_monte_carlo:
	./monte_carlo 1000000000

execute_mpi_monte_carlo:
	mpirun -np 4 mpi_monte_carlo 1000000000

execute_mpi_montecarlo_reduce:
	mpirun -np 4 mpi_montecarlo_reduce 1000000000

execute_mpi_master_slave:
	mpirun -np 4 mpi_master_slave 100 10 1000000000

execute_mpi_master_slave_desviopadrao:
	mpirun -np 4 mpi_master_slave_desviopadrao 100 1000000

clear:
	rm -rf mpi_hello mpi_hello2 mpi_run_vect mpi_sum_vect mpi_sum_reduce mpi_monte_carlo mpi_montecarlo_reduce monte_carlo mpi_master_slave search_in_vec mpi_encontra_minimo mpi_ordenacao mpi_master_slave_desviopadrao






