#include <stdio.h>
#include <string.h>
#include <iostream>

/*
matrix-vector multiplication
*/

void Mat_vect_mult(int local_A[] /*in*/, int local_x[] /*in*/, int local_y[] /*out*/, int local_m /*in*/,
	int n /*in*/);

int main(void) {
	int my_rank, comm_sz, m = 16, n = 4;
	int A[16] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 0, 1, 2, 5 };
	int x[4] = { 0, 1, 1, 2 };
	int y[4];

	printf("A:\n");
	for (int i = 0; i < m; i++) {
		printf("%d:%d\n", i, A[i]);
	}

	printf("X:\n");
	for (int i = 0; i < n; i++) {
		printf("%d:%d\n", i, x[i]);
	}

	Mat_vect_mult(A, x, y, m, n);

	printf("A*X:\n");
	for (int i = 0; i < m / n; i++)
		printf("%d: %d\n", i, y[i]);

	system("pause");
	return 0;
}


// Serial matrix-vector multiplication
void Mat_vect_mult(int A[] /*in*/, int x[] /*in*/, int y[] /*out*/, int m /*in*/, int n /*in*/) {
	int i, j;
	for (i = 0; i < m / n; i++) {
		y[i] = 0;
		for (j = 0; j < n; j++) {
			y[i] += A[i * n + j] * x[j];
		}
	}
}
