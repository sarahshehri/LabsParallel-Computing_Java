#include <stdio.h>
#include <string.h>
#include <iostream>

/*
computing _PI
*/

void Sum(int n/*in*/, double* sum /*out*/);

int main(int argc, char* argv[]) {

	int n = 100000000;
	double sum = 0.0;

	Sum(n, &sum);

	printf("for n = %d\nsum:%f\n", n, 4.0 * sum);

	//system("pause");
	return 0;
}

void Sum(int n/*in*/, double* sum /*out*/) {
	double factor = 1.0;

	for (int i = 0; i < n; i++, factor = -factor) {
		*sum += factor / (2 * i + 1);
	}

}
