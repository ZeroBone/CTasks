#include <stdio.h>
#include <stdlib.h>

/*
1, 2, 3, 4, 5 : 1, 3, 5
-9, 28, 1, 0, 6 : 1
0, 0, -1, 3, 7 : 3, 7
*/

int main() {
	
	int arrayLength, i;
	
	printf("Enter array length: ");
	
	scanf("%d", &arrayLength);
	
	if (arrayLength < 1) {
		
		printf("%s\n", "Invalid array length!");
		
		system("pause");
		
		return 1;
		
	}
	
	int *array = (int*)calloc(arrayLength, sizeof(int));
	
	if (array == NULL) {
		
		printf("Error allocating memory.");
		
		system("pause");
		
		return 1;
		
	}
	
	printf("Enter elements:\n");
	
	for (i = 0; i < arrayLength; i++) {
		
		scanf("%d", array + i);
		
	}
	
	int elementsCount, currentElement;
	
	for (i = 0, elementsCount = 0; i < arrayLength; i++) {
		
		currentElement = *(array + i);
		
		if (currentElement > 0 && currentElement % 2 == 1) {
			
			elementsCount++;
			
		}
		
	}
	
	int *newArray = (int*)calloc(elementsCount, sizeof(int));
	
	if (newArray == NULL) {
		
		printf("Error allocating memory.");
		
		system("pause");
		
		return 1;
		
	}
	
	for (i = 0, elementsCount = 0; i < arrayLength; i++) {
		
		currentElement = *(array + i);
		
		if (currentElement > 0 && currentElement % 2 == 1) {
			
			*(newArray + elementsCount) = currentElement;
			
			elementsCount++;
			
		}
		
	}
	
	free(array);
	
	printf("New array. Length: %d\n", elementsCount);
	
	for (i = 0; i < elementsCount; i++) {
		
		printf("%d ", newArray[i]);
		
	}
	
	free(newArray);
	
	printf("\n");
	
	system("pause");
	
	return 0;
	
}
