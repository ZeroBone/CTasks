#include <stdio.h>
#include <stdlib.h>

/*
Matrix:
   1.000   0.000   0.000
   0.000   1.000   0.000
   0.000   0.000   1.000
Average value of main line: 1.000000
===================
Matrix:
   5.000  -4.000
  12.000   3.600
Average value of main line: 4.300000
===================
Matrix:
   1.000   2.000
   3.000   4.000
Average value of main line: 2.500000
*/

int solution1();
int solution2();

int main() {
	
	int exitCode;
	
	/* exitCode = solution1(); */
	exitCode = solution2();
	
	system("pause");
	
	return exitCode;
	
}

int solution1() {
	
	int matrixSize, x, y;
	double average;
	
	printf("Enter matrix size: ");
	
	scanf("%d", &matrixSize);
	
	if (matrixSize <= 0) {
		
		printf("Invalid matrix size entered.\n");
		
		return 1;
		
	}
	
	double matrix[matrixSize][matrixSize];
	
	printf("Enter %dx%d matrix elements:\n", matrixSize, matrixSize);
	
	for (y = 0; y < matrixSize; y++) {
		
		for (x = 0; x < matrixSize; x++) {
			
			scanf("%lf", &matrix[y][x]);
			
		}
		
	}
	
	printf("Matrix:\n");
	
	for (y = 0; y < matrixSize; y++) {
		
		for (x = 0; x < matrixSize; x++) {
			
			printf("%8.3f", matrix[y][x]);
			
		}
		
		printf("\n");
		
	}
	
	average = 0;
	
	for (y = 0; y < matrixSize; y++) {
		
		average += matrix[y][y];
		
	}
	
	average /= matrixSize;
	
	printf("Average value of main line: %lf\n", average);
	
	return 0;
	
}

int solution2() {
	
	int matrixSize, x, y;
	
	double **matrix, average;
	
	printf("Enter matrix size: ");
	
	scanf("%d", &matrixSize);
	
	if (matrixSize <= 0) {
		
		printf("Invalid matrix size entered.\n");
		
		return 1;
		
	}
	
	/* memory allocation */
	
	matrix = (double**)calloc(matrixSize, sizeof(double*));
	
	if (matrix == NULL) {
		
		printf("Could not allocate memory.\n");
		
		return 2;
		
	}
	
	for (y = 0; y < matrixSize; y++) {
		
		matrix[y] = (double*)calloc(matrixSize, sizeof(double));
		
		if (matrix[y] == NULL) {
			
			for (x = 0; x < y; x++) { /* x is confusing here, it's just a counter */
				
				free(matrix[x]);
				
			}
			
		}
		
	}
	
	/* input */
	
	
	printf("Enter %dx%d matrix elements:\n", matrixSize, matrixSize);
	
	for (y = 0; y < matrixSize; y++) {
		
		for (x = 0; x < matrixSize; x++) {
			
			scanf("%lf", &matrix[y][x]);
			
		}
		
	}
	
	/* output */
	
	printf("Matrix:\n");
	
	for (y = 0; y < matrixSize; y++) {
		
		for (x = 0; x < matrixSize; x++) {
			
			printf("%8.3f", matrix[y][x]);
			
		}
		
		printf("\n");
		
	}
	
	/* calculation */
	
	average = 0;
	
	for (y = 0; y < matrixSize; y++) {
		
		average += matrix[y][y];
		
	}
	
	average /= matrixSize;
	
	printf("Average value of main line: %lf\n", average);
	
	return 0;
	
}
