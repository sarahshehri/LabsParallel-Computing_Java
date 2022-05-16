#include "stdafx.h"
#include <stdio.h>
#include <string.h>
#include <mpi.h>
#include <iostream>

int main(void) {
	int comm_sz;
	int my_rank;
	int sum;
	MPI_Init(NULL, NULL);
	MPI_Comm_size(MPI_COMM_WORLD, &comm_sz);
	MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

	MPI_Allreduce(&my_rank, &sum, 1, MPI_INT, MPI_SUM, MPI_COMM_WORLD);

    printf("Process %d: Sum rank of %d processes is %d!\n", my_rank, comm_sz, sum);

	MPI_Finalize();
	//system("pause");
	return 0;
} 
