#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <windows.h>
#include <math.h>
#include <float.h>
#define MAX_FNAME_LENGTH 50

char *outputFileName = "output.txt";

int main() {
	
	setlocale(LC_ALL, "Russian");
	
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	
	char inputFileName[MAX_FNAME_LENGTH];
	
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
	
	double matrixElement;
	double sum = 0;
	double minRowElement = DBL_MAX, maxRowElement = DBL_MIN;
	
	while (fscanf(inputFile, "%lf", &matrixElement) != EOF) {
		
		printf("Current matrix element: %lf\n", matrixElement);
		
		sum += matrixElement;
		
		if (matrixElement > maxRowElement) {
			maxRowElement = matrixElement;
		}
		
		if (matrixElement < minRowElement) {
			minRowElement = matrixElement;
		}
		
		fprintf(outputFile, "%.2lf", matrixElement);
		
		if (fgetc(inputFile) == '\n') {
			
			puts("End of line");
			
			/* it is also good to check that minRowElement and maxRowElement are not DBL_MIN/DBL_MAX */
			
			fprintf(outputFile, " %.2f ", sum);
			fprintf(outputFile, "%.2f ", minRowElement);
			fprintf(outputFile, "%.2f", maxRowElement);
			
			fputc('\n', outputFile);
			
			sum = 0;
			minRowElement = DBL_MAX;
			maxRowElement = DBL_MIN;
			
		}
		else fputc(' ', outputFile);
		
	}
	
	fclose(inputFile);
	fclose(outputFile);
	
	system("pause");
	
	return 0;
	
}

