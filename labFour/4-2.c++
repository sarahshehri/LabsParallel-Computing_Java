#include <stdio.h>
#include <string.h>
#include <iostream>


/*
vector addition
*/

void Vector_sum(int x[], int y[], int z[], int n);

int main(void) {
	int x[8] = { 0, 0, 1, 1, 2, 2, 3, 3 };
	int y[8] = { 0, 0, 1, 1, 2, 2, 3, 3 };
	int z[8];
	int i, n = 8;

	Vector_sum(x, y, z, n);

	printf("X:\n");
	for (i = 0; i < n; i++)
		printf("%d: %d\n", i, x[i]);

	printf("Y:\n");
	for (i = 0; i < n; i++)
		printf("%d: %d\n", i, y[i]);

	printf("X+Y:\n");
	for (i = 0; i < n; i++)
		printf("%d: %d\n", i, z[i]);
	//tells the OS to run the pause program. This program waits to be terminated, and halts the exceution of the parent C program
	//system("pause");
	return 0;
}


void Vector_sum(int x[], int y[], int z[], int n) {
	int i;

	for (i = 0; i < n; i++)
		z[i] = x[i] + y[i];
}
