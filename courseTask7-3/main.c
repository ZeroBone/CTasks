#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_FNAME_LENGTH 50

void printFile(FILE*);

int main() {
	
	puts("Enter input file name:");
	
	char inputFileName[MAX_FNAME_LENGTH];
	
	fgets(inputFileName, MAX_FNAME_LENGTH, stdin);
	inputFileName[strlen(inputFileName) - 1] = '\0';
	
	FILE *inputFile;
	
	if ((inputFile = fopen(inputFileName, "r+")) == NULL) {
		
		perror("An error occurred while trying to open the output file for writing");
		
		system("pause");
		
		return 1;
		
	}
	
	puts("File contents:");
	printFile(inputFile);
	
	double first, last;
	
	fseek(inputFile, 0, SEEK_SET);
	
	fread(&first, sizeof(double), 1, inputFile);
	
	fseek(inputFile, -sizeof(double), SEEK_END);
	
	fread(&last, sizeof(double), 1, inputFile);
	
	printf("First: %lf Last: %lf\n", first, last);
	
	/* alter the contents */
	
	fseek(inputFile, 0, SEEK_SET);
	
	double current;
	
	while (fread(&current, sizeof(double), 1, inputFile) >= 1) {
		
		fseek(inputFile, -sizeof(double), SEEK_CUR);
		
		if (current > 0) {
			
			current += first;
			
		}
		else {
			
			current -= last;
			
		}
		
		fwrite(&current, sizeof(double), 1, inputFile);
		fseek(inputFile, 0, SEEK_CUR);
		
		/* fseek(inputFile, sizeof(double), SEEK_CUR); */
		
	}
	
	
	puts("New file contents:");
	printFile(inputFile);
	
	fclose(inputFile);
	
	system("pause");
	
	return 0;
	
}

void printFile(FILE *file) {
	
	fseek(file, 0, SEEK_SET);
	
	double current;
	
	while (fread(&current, sizeof(double), 1, file) >= 1) {
		
		printf("%lf\n", current);
		
	}
	
}
