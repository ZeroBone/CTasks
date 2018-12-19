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
	char doubleContainer[50];
	
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
	
	
	int maxRowWidth = 0, rowWidth;
	double matrixElement;
	
	while (fscanf(inputFile, "%lf", &matrixElement) != EOF) {
		
		sprintf(doubleContainer, "%.2f", matrixElement);
			
		rowWidth = strlen(doubleContainer);
		
		if (rowWidth > maxRowWidth) {
			
			maxRowWidth = rowWidth;
			
		}
					
		printf("Length: %d\n", rowWidth);
		
	}
	
	fseek(inputFile, 0, SEEK_SET);
	
	double sum = 0;
	double minRowElement = DBL_MAX, maxRowElement = DBL_MIN;
	int current;
	
	while (1) {
		
		current = fscanf(inputFile, "%lf", &matrixElement);
		
		if (current != EOF) {
			
			printf("Current matrix element: %.2f\n", matrixElement);
			
			sum += matrixElement;
		
			if (matrixElement > maxRowElement) {
				maxRowElement = matrixElement;
			}
			
			if (matrixElement < minRowElement) {
				minRowElement = matrixElement;
			}
			
			/*fprintf(outputFile, "%.2f", matrixElement);*/
			writeDoubleAligned(outputFile, doubleContainer, matrixElement, maxRowWidth);
			
		}
		
		if (current == EOF || fgetc(inputFile) == '\n') {
			
			puts("End of line");
			
			/* it is also good to check that minRowElement and maxRowElement are not DBL_MIN/DBL_MAX */
			
			/*fputc(' ', outputFile);*/
			
			writeDoubleAligned(outputFile, doubleContainer, sum, maxRowWidth);
			writeDoubleAligned(outputFile, doubleContainer, minRowElement, maxRowWidth);
			writeDoubleAligned(outputFile, doubleContainer, maxRowElement, maxRowWidth);
			
			/*fprintf(outputFile, " %.2f ", sum);
			fprintf(outputFile, "%.2f ", minRowElement);
			fprintf(outputFile, "%.2f", maxRowElement);*/
			
			sum = 0;
			minRowElement = DBL_MAX;
			maxRowElement = DBL_MIN;
			
			if (current == EOF) break;
			else fputc('\n', outputFile);
			
		}
		
	}
	
	fclose(inputFile);
	fclose(outputFile);
	
	system("pause");
	
	return 0;
	
}

void writeDoubleAligned(FILE *file, char *container, double value, int maxWidth) {
	
	int width = sprintf(container, "%.2f", value);
	
	int i;	
	for (i = maxWidth + 1 - width; i > 0; i--) {
		
		fputc(' ', file);
		
	}
	
	fputs(container, file);
	
}
