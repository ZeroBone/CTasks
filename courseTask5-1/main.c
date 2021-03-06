#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define MATRIX_X 3
#define MATRIX_Y 3
#define ARRAY_SIZE 3
#define COMPARISON_EPSILON 1e-6

double* maxArrayElement(double* array, const unsigned int length, int *maxCount, const double epsilon);
void inputDoubleArray(double* arr, unsigned int length);
void outputMatrix(double* matrix, unsigned int y, unsigned int x);

/*
array = 1, 2, 3
Matrix:
    1.00    2.00    3.00
    4.00    5.00    6.00
    7.00    8.00    9.00
Altered matrix:
    1.00    2.00    3.00
    4.00    5.00    6.00
    7.00    8.00    3.00
New array:
    1.00    2.00    9.00
*/

/*
array = 9, 13, 13
Max array element: 13.000000 Index: 1 Count: 2
There is more than one max element in the array.
*/

/*
array = -6, 2, 2
Max array element: -6.000000 Index: 0 Count: 1
Matrix:
    6.00    4.00    3.00
    2.00    0.00   -4.00
   -1.00   -2.00    3.00
Altered matrix:
   -6.00    4.00    3.00
    2.00    0.00   -4.00
   -1.00   -2.00    3.00
New array:
    6.00    2.00    2.00
*/

/*
array = -18, 6, 1
Max array element: -18.000000 Index: 0 Count: 1
Matrix:
    1.00    5.00    8.00
   -4.00    0.00    7.00
    8.00   -2.00    1.00
There is more than one max element in the matrix.
*/

int main() {
	
	double array[ARRAY_SIZE];
	double matrix[MATRIX_Y][MATRIX_X], temp;
	int maxCount;
	double* maxArrayEl;
	double* maxMatrixElement;
	
	/* array input */
	
	printf("Enter array (length=%d):\n", ARRAY_SIZE);
	inputDoubleArray(array, ARRAY_SIZE);
	maxArrayEl = maxArrayElement(array, ARRAY_SIZE, &maxCount, COMPARISON_EPSILON);
	
	printf("Array:\n");
	
    outputMatrix(array, 1, ARRAY_SIZE);
	
	printf("Max array element: %lf Index: %d Count: %d\n", *maxArrayEl, maxArrayEl - array, maxCount);
	
	if (maxCount != 1) {
		
		printf("There is more than one max element in the array.\n");
		system("pause");
		return 1;
		
	}
	
	/* matrix i/o */
	
	printf("Enter %dx%d matrix elements:\n", MATRIX_Y, MATRIX_X);
	inputDoubleArray(matrix, MATRIX_Y * MATRIX_X);
	
	printf("Matrix:\n");
	outputMatrix(matrix, MATRIX_Y, MATRIX_X);
	
/*	double currentElementAbs, maxMatrixElement = fabs(matrix[0][0]);*/
	
	maxMatrixElement = maxArrayElement((double*)matrix, MATRIX_X * MATRIX_Y, &maxCount, COMPARISON_EPSILON);
	
	if (maxCount != 1) {
		
		printf("There is more than one max element in the matrix.\n");
		system("pause");
		return 1;
		
	}
	
	temp = *maxArrayEl;
	
	*maxArrayEl = *maxMatrixElement;
	
	*maxMatrixElement = temp;
	
	printf("Altered matrix:\n");
	outputMatrix(matrix, MATRIX_Y, MATRIX_X);
	
	printf("New array:\n");
    outputMatrix(array, 1, ARRAY_SIZE);
	
	system("pause");
	
	return 0;
	
}

double* maxArrayElement(double* array, const unsigned int length, int *maxCount, const double epsilon) {
	
	double* pointerToMax = array;
    int i;
	
	if (maxCount != NULL) *maxCount = 1;
	
	for (i = 1; i < length; i++) {
		
        if (maxCount != NULL && (fabs(array[i] - *pointerToMax) < epsilon)) {
			
			(*maxCount)++;
			
		}
        else if (fabs(array[i]) > fabs(*pointerToMax)) {
			
			pointerToMax = array + i;
			
			if (maxCount != NULL) {
				*maxCount = 1;
			}
			
		}
		
	}
	
	return pointerToMax;
	
}

/*int maxArrayElement(const double* array, const unsigned int length, int *maxCount, const double epsilon) {
	
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
	
}*/

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
