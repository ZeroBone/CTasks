#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_FNAME_LENGTH 50

int main() {
	
	int elementCount;
	
	puts("Enter the amount of doubles:");
	scanf("%d", &elementCount);
	getc(stdin);
	
	if (elementCount <= 0) {
		
		puts("Negative count entered.");
		
		system("pause");
		
		return 1;
		
	}
	
	puts("Enter output file name:");
	
	char outputFileName[MAX_FNAME_LENGTH];
	
	fgets(outputFileName, MAX_FNAME_LENGTH, stdin);
	outputFileName[strlen(outputFileName) - 1] = '\0';
	
	FILE *outputFile;
	
	if ((outputFile = fopen(outputFileName, "w")) == NULL) {
		
		perror("An error occurred while trying to open the output file for writing");
		
		system("pause");
		
		return 2;
		
	}
	
	printf("Enter values:\n");
	
	double currentValue, *p;
	int i;
	/* int j; */
	for (i = 0; i < elementCount; i++) {
		
		scanf("%lf", &currentValue);
		
		p = malloc(sizeof(double));
		
		if (p == NULL) {
		
			perror("Error allocation memory");
			
			system("pause");
			
			return 3;
			
		}
		
		*p = currentValue;
		
		fwrite(p, sizeof(double), 1, outputFile);
		
		/*for (j = 0; j < sizeof(double); j++) {
			
			fputc(*((char*)p), outputFile);
			
		}*/
		
		free(p);
		
	}
	
	fclose(outputFile);
		
	system("pause");
	
	return 0;
	
}
