#include "stdafx.h"
#include <stdio.h>
#include <string.h>
#include <mpi.h>
#include <iostream>

/*
matrix-vector multiplication
*/

void Mat_vect_mult(int local_A[] /*in*/, int x[] /*in*/, int local_y[] /*out*/, int local_m /*in*/,
	int n /*in*/, MPI_Comm comm /*in*/);

int main(void) {
	int my_rank, comm_sz, m = 8/*number of rows*/, n = 4 /*number of columns*/, local_m;
	int A[32] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31 }; // m*n
	int x[4] = { 0, 1, 3, 4 }; // n
	int y[8]; // m
	int local_A[8]; // local_m * n
	int local_y[2]; // local_m

	MPI_Init(NULL, NULL);
	MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
	MPI_Comm_size(MPI_COMM_WORLD, &comm_sz);

	local_m = m / comm_sz;

	printf("Proccess %d\n", my_rank);

	MPI_Scatter(A, local_m*n, MPI_INT, local_A, local_m*n, MPI_INT, 0, MPI_COMM_WORLD);
	//printf("local_A\n");
	//for (int i = 0; i<local_m*n; i++) {
	//	printf("%d:%d\n", i, local_A[i]);
	//}

	double local_start, local_finish, local_elapsed, elapsed;
	MPI_Barrier(MPI_COMM_WORLD);


	local_start = MPI_Wtime();

	Mat_vect_mult(local_A, x, local_y, local_m, n, MPI_COMM_WORLD);

	local_finish = MPI_Wtime();
	local_elapsed = local_finish - local_start;

	MPI_Reduce(&local_elapsed, &elapsed, 1, MPI_DOUBLE, MPI_MAX, 0, MPI_COMM_WORLD);

	printf("Proc %d > Elapsed time = %f seconds\n", my_rank, local_elapsed);



	MPI_Gather(local_y, local_m, MPI_INT, y, local_m, MPI_INT, 0, MPI_COMM_WORLD);

	//printf("local_y:\n");
	//for (int i = 0; i<local_m; i++)
	//	printf("%d: %d\n", i, local_y[i]);

	if (my_rank == 0) {
		printf("A:\n");
		for (int i = 0; i<m*n; i++) {
			printf("%d:%d\n", i, A[i]);
		}

		printf("X:\n");
		for (int i = 0; i<n; i++) {
			printf("%d:%d\n", i, x[i]);
		}

		printf("A*X:\n");
		for (int i = 0; i<m; i++)
			printf("%d: %d\n", i, y[i]);

		printf("Max Elapsed time = %f seconds\n", elapsed);
	}

	MPI_Finalize();
	//system("pause");
	return 0;
}

// An MPI matrix-vector multiplication function
void Mat_vect_mult(int local_A[] /*in*/, int x[] /*in*/, int local_y[] /*out*/, int local_m /*in*/,
	int n /*in*/, MPI_Comm comm /*in*/) {
	int local_i, j;

	MPI_Bcast(x, n, MPI_INT, 0, comm);

	for (local_i = 0; local_i < local_m; local_i++) {
		local_y[local_i] = 0;
		for (j = 0; j < n; j++)
			local_y[local_i] += local_A[local_i*n + j] * x[j];
	}
}
