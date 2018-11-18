#include <stdio.h>
#include <stdlib.h>
#define MATRIX_M 3
#define MATRIX_N 3

void inputDoubleArray(double* arr, unsigned int length);

void outputMatrix(double* matrix, unsigned int y, unsigned int x, char* formatString);

void processMatrix(double* matrix, unsigned int sizeY, unsigned int sizeX);

int main() {
	
	double matrixB[MATRIX_M][MATRIX_N];
	
	double matrixC[MATRIX_M][MATRIX_N];
	int x, y;
	
	printf("Enter B(%d,%d) matrix elements:\n", MATRIX_M, MATRIX_N);
	
	inputDoubleArray(matrixB, MATRIX_M * MATRIX_N);
	
	printf("Enter C(%d,%d) matrix elements:\n", MATRIX_M, MATRIX_N);
	
	inputDoubleArray(matrixC, MATRIX_M * MATRIX_N);
	
	printf("Matrix B:\n");

	processMatrix(matrixB, MATRIX_M, MATRIX_M);
	
	printf("Matrix C:\n");
	
	processMatrix(matrixC, MATRIX_M, MATRIX_M);
	
	system("pause");
	
	return 0;
	
}

void processMatrix(double* matrix, unsigned int sizeY, unsigned int sizeX) {
	
	unsigned int x, y, positiveCount;
	
	for (y = 0; y < sizeY; y++) {
		
		positiveCount = 0;
		
		for (x = 0; x < sizeX; x++) {
			
			if (matrix[y * sizeX + x] > 0) {
				
				positiveCount++;
				
			}
			
		}
		
		if (positiveCount == 2) {
			
			printf("Line %d contains exactly 2 positive values.\n", y + 1);
			
		}
		else {
			
			printf("Line %d doesn't contain 2 positive values.\n", y + 1);
			
		}
		
		
	}
	
}

void inputDoubleArray(double* arr, unsigned int length) {
	
	for (; length > 0; length--) {
		
		scanf("%lf", arr++);
		
	}
	
}

void outputMatrix(double* matrix, unsigned int y, unsigned int x, char* formatString) {
	
	unsigned int xCounter;
	
	if (formatString == NULL) {
		
		formatString = "%8.2f";
		
	}
	
	for (; y > 0; y--) {
		
		for (xCounter = 0; xCounter < x; xCounter++) {
			
			printf(formatString, *matrix++);
			
		}
		
		printf("\n");
		
	}
	
}
