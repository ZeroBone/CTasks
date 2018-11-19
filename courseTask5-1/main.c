#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define MATRIX_X 3
#define MATRIX_Y 3
#define ARRAY_SIZE 3
#define COMPARISON_EPSILON 1e-6

int maxArrayElement(double* array, unsigned int length, int* maxCount, double epsilon);
void inputDoubleArray(double* arr, unsigned int length);
void outputArray(double* array, int length);
void outputMatrix(double* matrix, unsigned int y, unsigned int x);

int main() {
	
	double array[ARRAY_SIZE];
	
	int x, y, i, maxArrayEl, maxCount;
	
	printf("Enter array (length=%d):\n", ARRAY_SIZE);
	
	inputDoubleArray(array, ARRAY_SIZE);
	
	maxArrayEl = maxArrayElement(array, ARRAY_SIZE, &maxCount, COMPARISON_EPSILON);
	
	if (maxCount != 1) {
		
		printf("There is more than one max element in the array.\n");
		
		system("pause");
	
		return 1;
		
	}
	
	double matrix[MATRIX_Y][MATRIX_X];
	
	printf("Enter %dx%d matrix elements:\n", MATRIX_Y, MATRIX_X);
	
	inputDoubleArray(matrix, MATRIX_Y * MATRIX_X);
	
	printf("Matrix:\n");
	
	outputMatrix(matrix, MATRIX_Y, MATRIX_X);
	
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
		matrix[maxMatrixElements[offset] / MATRIX_X][maxMatrixElements[offset] % MATRIX_X] = array[maxArrayEl];
		
	}
	
	array[maxArrayEl] = maxMatrixElement;
	
	outputMatrix(matrix, MATRIX_Y, MATRIX_X);
	
	system("pause");
	
	return 0;
	
}

int maxArrayElement(double* array, unsigned int length, int *maxCount, double epsilon) {
	
	int maxIndex = 0, i;
	
	if (maxCount != NULL) *maxCount = 1;
	
	for (i = 1; i < length; i++) {
		
		if (maxCount != NULL && fabs(array[i]) - fabs(array[maxIndex]) < epsilon) {
			
			(*maxCount)++;
			
		}
		else if (fabs(array[i]) > fabs(array[maxIndex])) {
			
			maxIndex = i;
			if (maxCount != NULL) *maxCount = 1;
			
		}
		
	}
	
	return maxIndex;
	
}

void inputDoubleArray(double* arr, unsigned int length) {
	
	for (; length > 0; length--) {
		
		scanf("%lf", arr++);
		
	}
	
}

void outputArray(double* array, int length) {
	
	int i;
	
	for (i = 0; i < length; i++) {
		
		printf("%lf ", array[i]);
		
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
