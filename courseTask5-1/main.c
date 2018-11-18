#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MATRIX_X 3
#define MATRIX_Y 3
#define ARRAY_SIZE 3
#define COMPARISON_EPSILON 1e-6

void inputDoubleArray(double* arr, unsigned int length);

void outputMatrix(double* matrix, unsigned int y, unsigned int x, char* formatString);

/*void inputArray(void* arr, size_t element, unsigned int length) {
	
	switch (element) {
		
		case sizeof(double):
			
			for (; length > 0; length--) {
				
				scanf("%lf", (double*)arr);
				
			}
			
			break;
			
	}
	

	
}*/

int main() {
	
	double array[ARRAY_SIZE];
	
	int x, y, i, maxArrayElementIndex, maxArrayElementCount;
	
	printf("Enter array (length=%d):\n", ARRAY_SIZE);
	
	inputDoubleArray(array, ARRAY_SIZE);
	
	maxArrayElementIndex = 0;
	maxArrayElementCount = 1;
	
	for (i = 1; i < ARRAY_SIZE; i++) {
		
		if (fabs(array[i]) - fabs(array[maxArrayElementIndex]) < COMPARISON_EPSILON) {
			
			maxArrayElementCount++;
			
		}
		else if (fabs(array[i]) > fabs(array[maxArrayElementIndex])) {
			
			maxArrayElementIndex = i;
			maxArrayElementCount = 1;
			
		}
		
	}
	
	if (maxArrayElementCount != 1) {
		
		printf("There is more than one max element in the array.\n");
		
		system("pause");
	
		return 1;
		
	}
	
	double matrix[MATRIX_Y][MATRIX_X];
	
	printf("Enter %dx%d matrix elements:\n", MATRIX_Y, MATRIX_X);
	
	inputDoubleArray(matrix, MATRIX_Y * MATRIX_X);
	
	printf("Matrix:\n");
	
	outputMatrix(matrix, MATRIX_Y, MATRIX_X, NULL);
	
	/* double* maxMatrixElements[MATRIX_X * MATRIX_Y]; */
	int maxMatrixElements[MATRIX_X * MATRIX_Y];
	int pushCounter = 0;
	int offset = 0;
	
	double currentElementAbs, maxMatrixElement = fabs(matrix[0][0]);
	
	for (y = 0; y < MATRIX_Y; y++) {
		
		for (x = 0; x < MATRIX_X; x++) {
			
			currentElementAbs = fabs(matrix[y][x]);
			
			/* printf("Current: %lf Max: %lf\n", currentElementAbs, maxMatrixElement); */
			
			if (currentElementAbs > maxMatrixElement) {
				
				maxMatrixElement = currentElementAbs;
				
				/* maxMatrixElements[pushCounter] = *(matrix + y) + x;*/
				maxMatrixElements[pushCounter] = y * MATRIX_X + x;
				
				offset = pushCounter++;
				
			}
			else if (fabs(currentElementAbs - maxMatrixElement) < COMPARISON_EPSILON) {
				
				/* maxMatrixElements[pushCounter++] = *(matrix + y) + x; */
				maxMatrixElements[pushCounter++] = y * MATRIX_X + x;
				
			}
			
		}
		
	}
	
	printf("Max elements found in matrix: %d\n", pushCounter - offset);
	
	for (; offset < pushCounter; offset++) {
		
		/* *maxMatrixElements[offset] = array[maxArrayElementIndex]; */
		matrix[maxMatrixElements[offset] / MATRIX_X][maxMatrixElements[offset] % MATRIX_X] = array[maxArrayElementIndex];
		
	}
	
	array[maxArrayElementIndex] = maxMatrixElement;
	
	outputMatrix(matrix, MATRIX_Y, MATRIX_X, NULL);
	
	system("pause");
	
	return 0;
	
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
