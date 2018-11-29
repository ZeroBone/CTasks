#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#define MAX_NAME_LENGTH 50

int main(int argc, char *argv[]) {
	
	setlocale(LC_ALL, "Russian");
	
	char *inputFile[MAX_NAME_LENGTH];
	
	if (argc < 2) {
		
		printf("Insifficient amount of args specified.\n");
		
		printf("Enter input file name:\n");
		fgets(inputFile, MAX_NAME_LENGTH, stdin);
		
	}
	else {
		
		strcpy(inputFile, argv[1]);
		
	}
	
	printf("Input file: ");
	puts(inputFile);
	
	FILE *file = fopen(inputFile, "r+");
	
	int current;
	char* currentPhrase[50];
	
	/*while ((current = fgetc(file)) != EOF) {
		
		printf("%c", current);
		
		
		
	}*/
	
	while (fscanf(file, )) {
		
		
		
	}
	
	fclose(file);
	
	system("pause");
	
	return 0;
	
}
