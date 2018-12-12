#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define MAX_FNAME_LENGTH 50
#define EPSILON 1e-6

/*
Enter input file name:
five.bin
File contents:
4.000000
5.000000
6.000000
7.000000
8.000000
First: 4.000000 Last: 8.000000
New file contents:
8.000000
9.000000
10.000000
11.000000
12.000000
==========================
Enter input file name:
three.bin
File contents:
2.000000
3.000000
367869.000000
First: 2.000000 Last: 367869.000000
New file contents:
4.000000
5.000000
367871.000000
==========================
Enter input file name:
n.bin
File contents:
-8.000000
-3.000000
222.000000
-29.000000
-40.000000
0.000000
First: -8.000000 Last: 0.000000
New file contents:
-8.000000
-3.000000
214.000000
-29.000000
-40.000000
0.000000
*/

void printFile(FILE*);

int main() {
	
	puts("Enter input file name:");
	
	char inputFileName[MAX_FNAME_LENGTH];
	
	fgets(inputFileName, MAX_FNAME_LENGTH, stdin);
	inputFileName[strlen(inputFileName) - 1] = '\0';
	
	FILE *inputFile;
	
	if ((inputFile = fopen(inputFileName, "r+b")) == NULL) {
		
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
	
	if (fabs(first) > EPSILON || fabs(last) > EPSILON) {
		
		fseek(inputFile, 0, SEEK_SET);
	
		double current;
		
		while (fread(&current, sizeof(double), 1, inputFile) == 1) {
			
			if (fabs(current) < EPSILON) {
				
				continue;
				
			}
			
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
