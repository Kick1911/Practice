#include <mpi.h>
#include <stdio.h>

#define TAG 123

int main(int argc, char** argv){
	int rank;
	int a[500], b[500];

	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	if(rank == 0){
		double A[5] = {1,2,3,4,5};
		MPI_Send(A, 5, MPI_DOUBLE, 1, TAG, MPI_COMM_WORLD);
		/* MPI_Send(&a[500],500, MPI_INT, 1, 0, MPI_COMM_WORLD);
		MPI_Recv(b, 500, MPI_INT, 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE); */
	}
	else if(rank == 1){
		double B[5];
		MPI_Recv(B, 5, MPI_DOUBLE, 0, TAG, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
		printf("%f\n",B[4]);
		/* MPI_Recv(b, 500, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
		MPI_Send(b,500, MPI_INT, 0, 0, MPI_COMM_WORLD); */
	}
	MPI_Finalize();
	return 0;
	
}
