#ifndef VEC_ADD_MPI_C
#define VEC_ADD_MPI_C
#include <stdio.h>
#include <mpi.h>
#include <assert.h>
#include <vectoradd.h>

int main(int argc, char** argv){
	int rank, p, N = 100;
	int* array;

	MPI_Init(&argc,&argv);
	MPI_Barrier(MPI_COMM_WORLD);
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);
	MPI_Comm_size(MPI_COMM_WORLD,&p);
	int range = N/p;

	if( !(array = (int*)malloc(sizeof(int) * range)) ){
		printf("Could not allocate memory.\n");
		MPI_Finalize();
		exit(1);
	}

	/* assert(MPI_Bcast(array, 100, MPI_INT, 0, MPI_COMM_WORLD) == MPI_SUCCESS); */


	int i = 0;
	while( i < range ){
		array[i] = i + rank * range + 1;
		i++;
	}

	int* ptr = array;
	while( *ptr )
		printf("%d ",*ptr++);
	printf("\n");

	free(array);
	MPI_Finalize();
	return 0;
}
#endif
