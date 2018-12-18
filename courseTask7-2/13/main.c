#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <windows.h>
#include <math.h>
#define MAX_FNAME_LENGTH 100

int main() {
	
	setlocale(LC_ALL, "Russian");
	
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	
	char inputFileName[MAX_FNAME_LENGTH];
	char *outputFileName = "output.txt";
	char doubleContainer[20];
	
	FILE *inputFile, *outputFile;
	
	puts("Enter input file name:");
	
	fgets(inputFileName, MAX_FNAME_LENGTH, stdin);
	inputFileName[strlen(inputFileName) - 1] = '\0';
	
	printf("Input file name:");
	puts(inputFileName);
	
	if ((inputFile = fopen(inputFileName, "r")) == NULL) {
		
		perror("An error occurred while trying to read the file");
		
		system("pause");
		
		return 1;
		
	}
	
	if ((outputFile = fopen(outputFileName, "w")) == NULL) {
		
		perror("An error occurred while trying to open the output file for writing");
		
		system("pause");
		
		return 2;
		
	}
	
	/* file streams opened */
	
	int matrixElement, count = 0, xCount = 0, yCount = 1;
	int x, y, value, i, doubleSLength;
	int maxColumnWidth = 0;
	
	while (fscanf(inputFile, "%d", &matrixElement) != EOF) {
		
		count++;
		
		if (fgetc(inputFile) == '\n') {
			
			yCount++;
			
		}
		
		printf("Current matrix element: %d\n", matrixElement);
		
		/* calculate max width */
		
		/* printf("(COUNTING) Current value: %d\n", matrixElement); */
			
		doubleSLength = sprintf(doubleContainer, "%.2f", (double)matrixElement);
		puts(doubleContainer);
		
		/* doubleSLength = strlen(doubleContainer); */
		
		printf("(COUNTING) Current value length: %d\n", doubleSLength);
		
		if (doubleSLength > maxColumnWidth) maxColumnWidth = doubleSLength;
		
	}
	
	xCount = count / yCount;
	
	printf("This is a %dx%d matrix.\n", yCount, xCount);
	
	printf("Max column width: %d\n", maxColumnWidth);
	
	fseek(inputFile, 0, SEEK_SET);
	
	for (y = 0; y < yCount; y++) {
		
		for (x = 0; x < xCount; x++) {
			
			value = fscanf(inputFile, "%d", &matrixElement);
			
			if (fgetc(inputFile) != '\n') fseek(inputFile, -1, SEEK_CUR);
			
			printf("Current value: %d\n", matrixElement);
			
			if (value == EOF) {
				
				perror("Error writing matrix");
		
				system("pause");
				
				return 3;
				
				/* goto break2; */
				
			}
			
			printf("Value: %d x: %d count: %d\n", matrixElement, x, xCount);
			
			/*if (x == xCount - 2) {
				
				fprintf(outputFile, "%.2f\n", (double)matrixElement);
				
			}*/
			
			doubleSLength = sprintf(doubleContainer, "%.2f", (double)matrixElement);
				
			for (i = maxColumnWidth + (x != 0) - doubleSLength; i > 0; i--) {
				
				fputc(' ', outputFile);
				
			}
			
			/*fprintf(outputFile, "%s", doubleContainer);*/
			fputs(doubleContainer, outputFile);
			
			if (x == xCount - 1) fputc('\n', outputFile);
			
		}
		
	}
	/*break2: */
	
	fclose(inputFile);
	fclose(outputFile);
	
	system("pause");
	
	return 0;
	
}
