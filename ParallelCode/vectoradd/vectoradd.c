#include <omp.h>
#include <mpi.h>
#include <stdio.h>
#include <malloc.h>

#define TAG 123

void vectoradd(int* v1, int* v2, size_t length){
	printf("%d %d\n",v1[0],v1[length]);
	#pragma omp parallel num_threads(length)
	{
		int thread = omp_get_thread_num();
		v1[thread] = v1[thread] +  v2[thread];
	}
}

void display(int* array){
	while(*array)
		printf("%d ",*array++);
	printf("\n");
}

int main(int argc, char** argv){
	int rank, processors;
	const int root = 0;
	size_t compute_size = 1 << 12, size = 1 << 15;

	int* a = malloc(sizeof(int) * size);
	int* b = malloc(sizeof(int) * size);
	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &processors);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	if( rank == root ){
		int i = 0;
		while(i < size){
			a[i] = i+1;
			b[i] = i+1;
			i++;
		}
		a[i] = 0; b[i] = 0;
	}

	MPI_Bcast(a, size, MPI_INT, root, MPI_COMM_WORLD);
	MPI_Bcast(b, size, MPI_INT, root, MPI_COMM_WORLD);
	vectoradd(a + (compute_size*rank), b + (compute_size*rank), compute_size - 1);

	if( rank == root ){
		printf("%d\n",a[0]);
		printf("%d\n",a[size-1]);
	}

	free(a);free(b);
	MPI_Finalize();
	return 0;
}
