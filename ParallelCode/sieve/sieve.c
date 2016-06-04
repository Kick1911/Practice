#ifndef SIEVE_C
#define SIEVE_C
#define MIN(n1,n2) (((n1) < (n2))?(n1):(n2))

#include <sieve.h>
#include <mpi.h>
#include <stdio.h>
#include <math.h>

int main(int argc,char** argv){
	int count;
	double elapsed_time;
	int first;
	int global_count;
	int high_value, low_value;
	int i;
	int rank, p, n;
	int index;
	char* marked;
	int proc0_size;
	int prime;
	int size;

	MPI_Init(&argc, &argv);
	MPI_Barrier(MPI_COMM_WORLD);
	elapsed_time = -MPI_Wtime();

	MPI_Comm_rank(MPI_COMM_WORLD,&rank);
	MPI_Comm_size(MPI_COMM_WORLD,&p);

	if(argc != 2){
		if(!rank) printf("Command line: %s <m>\n", argv[0]);
		MPI_Finalize();
		exit(1);
	}
	
	n = atoi(argv[1]);

	low_value = 2 + BLOCK_LOW(rank, p, n-1);
	high_value = 2 + BLOCK_HIGH(rank, p, n-1);
	size = BLOCK_SIZE(rank, p, n-1);

	printf("process: %d low_value: %d high_value: %d size: %d\n", rank, low_value, high_value, size);

	proc0_size = (n-1)/p;

	if( (2 + proc0_size) < (int) sqrt((double) n) ){
		if(!rank) printf("Too many processes\n");
		MPI_Finalize();
		exit(1);
	}

	
	if( !(marked = (char*) malloc(size)) ){
		printf("Cannot allocate enough memory\n");
		MPI_Finalize();
		exit(1);
	}

	while( i < size ) marked[i++] = 0;
	if(!rank) index = 0;
	prime = 2;
	do{
		if(prime * prime > low_value)
			first = prime * prime - low_value;
		else{
			if(!(low_value % prime)) first = 0;
			else first = prime - (low_value % prime);
		}
		i = first;
		while( i < size ){
			marked[i] = 1;
			i += prime;
		}
		if(!rank){
			while(marked[++index]);
			prime = index + 2;
		}
		MPI_Bcast(&prime, 1, MPI_INT, 0, MPI_COMM_WORLD);
	}while( prime * prime <= n);
	count = 0;
	i = 0;
	printf("WTF\n");
	while( i < size )
		if(!marked[i++]) count++;
	MPI_Reduce(&count, &global_count, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
	
	elapsed_time += MPI_Wtime();

	if(!rank){
		printf("%d primes are less than or equal to %d\n",global_count, n);
		printf("Total elapsed time: %10.6f\n", elapsed_time);
	}

	MPI_Finalize();
 	return 0;
}
#endif
