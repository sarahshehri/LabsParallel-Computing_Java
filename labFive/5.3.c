#include <stdio.h>
#include <string.h>
#include <mpi.h>
#include <iostream>

const int MAX_STRING = 100;

int main(void) {
	int comm_sz;
	int my_rank;
	int year = 0;
	MPI_Init(NULL, NULL);
	MPI_Comm_size(MPI_COMM_WORLD, &comm_sz);
	MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

	if (my_rank == 0) {
		year = 2017;
		for (int p = 1; p < comm_sz; p++) {
			MPI_Send(&year, 1, MPI_INT, p, 0, MPI_COMM_WORLD);
		}
	}
	else {
		MPI_Recv(&year, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
		printf("Process %d received %d from process 0\n", my_rank, year);
	}

	MPI_Finalize();
	//system("pause");
	return 0;
}
