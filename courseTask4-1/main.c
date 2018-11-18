#include <stdio.h>
#include <stdlib.h>

#define MAX_ARR_LENGTH 45

/*
1, 2, 3, 4, 5 Max: 5 Min: 1 Sum: 9
5, 4, 3, 2, 1 Max: 5 Min: 1 Sum: 9
1, 10, 10, 5, 2 Max element and min element stay next to each other.
9, 8, 2, 2, 4 Min element comes more than 1 time.
1, 2, 6, 6, 3 Max element comes more than 1 time.
*/

int abs(int value);

int main() {
	
	int arrayLength;
	int i;
	
	printf("Enter array length:");
	
	scanf("%d", &arrayLength);
	
	if (arrayLength > MAX_ARR_LENGTH || arrayLength < 1) {
		
		printf("Invalid array length!\n");
		
		system("pause");
		
		return 0;
		
	}
	
	int a[arrayLength];
	
	printf("Enter array elements:\n");
	
	for (i = 0; i < arrayLength; i++) {
		
		scanf("%d", (a + i));
		
	}
	
	/*int a[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45};*/
	
	int minIndex = 0, maxIndex = 0;
	int minCount = 1, maxCount = 1;
	
	for (i = 1; i < arrayLength; i++) {
		
		if (a[i] == a[minIndex]) {
			
			minCount++;
			
			
		}
		else if (a[i] < a[minIndex]) {
			
			minIndex = i;
			minCount = 1;
			
		}
		
		if (a[i] == a[maxIndex]) {
			
			maxCount++;
			
		}
		else if (a[i] > a[maxIndex]) {
			
			maxIndex = i;
			maxCount = 1;
			
		}
		
	}
	
	if (abs(maxIndex - minIndex) == 1) {
		
		printf("Max element and min element stay next to each other.\n");
		
		system("pause");
		
		return 1;
		
	}
	
	if (minCount != 1) {
		
		printf("Min element comes more than 1 time.\n");
			
		system("pause");
			
		return 1;
		
	}
	
	if (maxCount != 1) {
		
		printf("Max element comes more than 1 time.\n");
		
		system("pause");
		
		return 1;
		
		
	}
	
	int sum = 0;
	
	if (maxIndex > minIndex) {
		
		for (i = minIndex + 1; i < maxIndex; i++) {
			
			sum += a[i];
			
		}
		
	}
	else {
		
		for (i = maxIndex + 1; i < minIndex; i++) {
			
			sum += a[i];
			
		}
		
	}
	
	printf("Max: %d Min: %d\n", a[maxIndex], a[minIndex]);
	printf("Sum: %d\n", sum);
	
	system("pause");
	
	return 0;
	
}

int abs(int v) {
	
	return v < 0 ? -v : v;
	
}
