#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define MATRIX_X 3
#define MATRIX_Y 3
#define ARRAY_SIZE 3
#define COMPARISON_EPSILON 1e-6

int maxArrayElement(const double* array, const unsigned int length, int* maxCount, const double epsilon);
void inputDoubleArray(double* arr, unsigned int length);
void outputArray(double* array, int length);
void outputMatrix(double* matrix, unsigned int y, unsigned int x);

int main() {
	
	double array[ARRAY_SIZE];
	int x, y, i, maxArrayEl, maxCount;
	
	/* array input */
	
	printf("Enter array (length=%d):\n", ARRAY_SIZE);
	inputDoubleArray(array, ARRAY_SIZE);
	maxArrayEl = maxArrayElement(array, ARRAY_SIZE, &maxCount, COMPARISON_EPSILON);
	
	printf("Max array element: %lf Index: %d Count: %d\n", array[maxArrayEl], maxArrayEl, maxCount);
	
	if (maxCount != 1) {
		
		printf("There is more than one max element in the array.\n");
		system("pause");
		return 1;
		
	}
	
	double matrix[MATRIX_Y][MATRIX_X], temp;
	
	/* matrix i/o */
	
	printf("Enter %dx%d matrix elements:\n", MATRIX_Y, MATRIX_X);
	inputDoubleArray(matrix, MATRIX_Y * MATRIX_X);
	
	printf("Matrix:\n");
	outputMatrix(matrix, MATRIX_Y, MATRIX_X);
	
	double currentElementAbs, maxMatrixElement = fabs(matrix[0][0]);
	
	int maxMatrixElementIndex = maxArrayElement(matrix, MATRIX_X * MATRIX_Y, &maxCount, COMPARISON_EPSILON);
	
	if (maxCount != 1) {
		
		printf("There is more than one max element in the matrix.\n");
		system("pause");
		return 1;
		
	}
	
	temp = array[maxArrayEl];
	
	array[maxArrayEl] = *((double*)matrix + maxMatrixElementIndex);
	
	*((double*)matrix + maxMatrixElementIndex) = temp;
	
	printf("Altered matrix:\n");
	outputMatrix(matrix, MATRIX_Y, MATRIX_X);
	
	system("pause");
	
	return 0;
	
	/*for (y = 0; y < MATRIX_Y; y++) {
		
		for (x = 0; x < MATRIX_X; x++) {
			
			currentElementAbs = fabs(matrix[y][x]);
			
			
			if (currentElementAbs > maxMatrixElement) {
				
				maxMatrixElement = currentElementAbs;
				maxMatrixElements[pushCounter] = y * MATRIX_X + x;
				
				offset = pushCounter++;
				
			}
			else if (fabs(currentElementAbs - maxMatrixElement) < COMPARISON_EPSILON) {
			
				maxMatrixElements[pushCounter++] = y * MATRIX_X + x;
				
			}
			
		}
		
	}*/
	
}

int maxArrayElement(const double* array, const unsigned int length, int *maxCount, const double epsilon) {
	
	int maxIndex = 0, i;
	
	if (maxCount != NULL) *maxCount = 1;
	
	for (i = 1; i < length; i++) {
		
		if (maxCount != NULL && (fabs(array[i] - array[maxIndex]) < epsilon)) {
			
			(*maxCount)++;
			
		}
		else if (fabs(array[i]) > fabs(array[maxIndex])) {
			
			maxIndex = i;
			
			if (maxCount != NULL) {
				*maxCount = 1;
			}
			
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
