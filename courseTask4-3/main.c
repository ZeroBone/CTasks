#include <stdio.h>
#include <stdlib.h>

#define MATRIX_Y 3
#define MATRIX_X 3

/*
Исходная матрица:
     1.0     2.0     3.0
     4.0     5.0     6.0
     7.0     8.0     9.0
Resulting matrix:
     1.0     2.0     3.0
     4.0     5.0     6.0
     7.0     8.0     9.0
===============
Исходная матрица:
     9.0     8.0     7.0
     6.0     5.0     4.0
     3.0     2.0     1.0
Resulting matrix:
     3.0     2.0     1.0
     6.0     5.0     4.0
     9.0     8.0     7.0
===============
Исходная матрица:
     -5.0    1.0     7.0
     0.0     0.0     1.0
     5.0     9.0     8.0
Resulting matrix:
     0.0     0.0     1.0
    -5.0     1.0     7.0
     5.0     9.0     8.0
*/

int main() {
	
	double matrix[MATRIX_Y][MATRIX_X];
	int x, y, k, yMin;
	
	double rowSums[MATRIX_Y], temp, currentSum;
	
	printf("Enter %dx%d matrix elements:\n", MATRIX_Y, MATRIX_X);
	
	for (y = 0; y < MATRIX_Y; y++) {
		
		for (x = 0; x < MATRIX_X; x++) {
			
			scanf("%lf", &matrix[y][x]);
			
		}
		
	}
	
	for (y = 0; y < MATRIX_Y; y++) {
		
		currentSum = 0;
		
		for (x = 0; x < MATRIX_X; x++) {
			
			currentSum += matrix[y][x];
			
		}
		
		rowSums[y] = currentSum;
		
	}
	
	for (y = 0; y < MATRIX_Y - 1; y++) {
		
		yMin = y;
		
		for (k = y + 1; k < MATRIX_Y; k++) {
			
			if (rowSums[k] < rowSums[yMin]) {
				
				yMin = k;
				
			}
			
		}
		
		/* swap [y] and [iMin] */
		
		temp = rowSums[y];
		rowSums[y] = rowSums[yMin];
		rowSums[yMin] = temp;
		
		for (x = 0; x < MATRIX_X; x++) {
			
			temp = matrix[y][x];
			matrix[y][x] = matrix[yMin][x];
			matrix[yMin][x] = temp;
			
		}
		
		
	}
	
	printf("Resulting matrix:\n");
	
	for (y = 0; y < MATRIX_Y; y++) {
		
		for (x = 0; x < MATRIX_X; x++) {
			
			printf("%8.1f", matrix[y][x]);
			
		}
		
		printf("\n");
		
	}
	
	system("pause");
	
	return 0;
	
}
