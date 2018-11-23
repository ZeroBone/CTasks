#include <stdio.h>
#include <stdlib.h>
#define MATRIX_M 3
#define MATRIX_N 3

void inputDoubleArray(double* arr, unsigned int length);
void processMatrix(double* matrix, unsigned int sizeY, unsigned int sizeX);
void outputMatrix(double* matrix, unsigned int y, unsigned int x);
int positiveElements(double* row, unsigned int rowLength);

/*
Matrix B:
    1.00    2.00    3.00
    4.00    5.00    6.00
    7.00    8.00    9.00

Line 1 doesn't contain 2 positive values.
Line 2 doesn't contain 2 positive values.
Line 3 doesn't contain 2 positive values.
Matrix C:
   -1.00    2.00    3.00
    1.00   -2.00    3.00
    1.00    2.00   -3.00

Line 1 contains exactly 2 positive values.
Line 2 contains exactly 2 positive values.
Line 3 contains exactly 2 positive values.
*/

/*
Matrix B:
    0.00   11.00    3.00
    6.00   98.00    2.00
   84.00   49.00   10.00

Line 1 contains exactly 2 positive values.
Line 2 doesn't contain 2 positive values.
Line 3 doesn't contain 2 positive values.
Matrix C:
   12.00   13.00   32.00
   41.00   65.00   35.00
   -9.00    1.00    0.00

Line 1 doesn't contain 2 positive values.
Line 2 doesn't contain 2 positive values.
Line 3 doesn't contain 2 positive values.
*/

/*
Matrix B:
    1.00    0.00   -1.00
   -0.00   -0.00   -0.00
 1066.00   -5.00  346.00

Line 1 doesn't contain 2 positive values.
Line 2 doesn't contain 2 positive values.
Line 3 contains exactly 2 positive values.
Matrix C:
    0.10    0.38   -0.20
    6.00    9.50  -64.00
   14.00    8.00  -45.00

Line 1 contains exactly 2 positive values.
Line 2 contains exactly 2 positive values.
Line 3 contains exactly 2 positive values.
*/

int main() {
	
	double matrixB[MATRIX_M][MATRIX_N];
	
	double matrixC[MATRIX_M][MATRIX_N];
	
	printf("Enter B(%d,%d) matrix elements:\n", MATRIX_M, MATRIX_N);
	
	inputDoubleArray(matrixB, MATRIX_M * MATRIX_N);
	
	printf("Enter C(%d,%d) matrix elements:\n", MATRIX_M, MATRIX_N);
	
	inputDoubleArray(matrixC, MATRIX_M * MATRIX_N);
	
	printf("Matrix B:\n");
	
	outputMatrix(matrixB, MATRIX_M, MATRIX_N);
	
	printf("\n");
	
	processMatrix(matrixB, MATRIX_M, MATRIX_N);
	
	printf("Matrix C:\n");
	
	outputMatrix(matrixC, MATRIX_M, MATRIX_N);
	
	printf("\n");
	
	processMatrix(matrixC, MATRIX_M, MATRIX_N);
	
	system("pause");
	
	return 0;
	
}

void processMatrix(double* matrix, unsigned int sizeY, unsigned int sizeX) {
     
     int y;
     for (y = 0; y < sizeY; y++) {
		
		if (positiveElements(matrix + (sizeX * y), sizeX) == 2) {
			
			printf("Line %d contains exactly 2 positive values.\n", y + 1);
			
		}
		else {
			
			printf("Line %d doesn't contain 2 positive values.\n", y + 1);
			
		}
		
	}
}

int positiveElements(double* row, unsigned int rowLength) {
	
	int count = 0;
	
	for (; rowLength > 0; rowLength--) {
		
		if (*row++ > 0) {
			
			count++;
			
		}
		
	}
	
	return count;
	
}

void inputDoubleArray(double* arr, unsigned int length) {
	
	for (; length > 0; length--) {
		
		scanf("%lf", arr++);
		
	}
	
}

void outputMatrix(double* matrix, unsigned int y, unsigned int x) {
	
	unsigned int xCounter;
	
	for (; y > 0; y--) {
		
		for (xCounter = 0; xCounter < x; xCounter++) {
			
			printf("%8.2f", *matrix++);
			
		}
		
		printf("\n");
		
	}
	
}
