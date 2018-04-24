CC=gcc 
CFLAGS=-Wall

compile_all:	compile_mpi_hello compile_mpi_hello2
compile_mpi_hello: mpi_hello.c
	mpicc -o mpi_hello mpi_hello.c


compile_mpi_hello2: mpi_hello.c
	mpicc -o mpi_hello2 mpi_hello2.c



