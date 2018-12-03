#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <windows.h>
#define MAX_FNAME_LENGTH 50

char phraseOk(char*);

int main(int argc, char *argv[]) {
	
	setlocale(LC_ALL, "Russian");
	
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	
	char inputFileName[MAX_FNAME_LENGTH];
	
	if (argc < 2) {
		
		printf("Enter input file name:\n");
		
		fgets(inputFileName, MAX_FNAME_LENGTH, stdin);
		
	}
	else {
		
		strcpy(inputFileName, argv[1]);
		
	}
	
	printf("Input file: ");
	puts(inputFileName);
	
	FILE *inputFile, *tempFile;
	
	if ((inputFile = fopen(inputFileName, "r")) == NULL) {
		
		perror("An error occurred while trying to read the file");
		
		system("pause");
		
		return 1;
		
	}
	
	if ((tempFile = fopen("temp.txt", "w")) == NULL) {
		
		perror("An error occurred while trying to create a temp file");
		
		system("pause");
		
		return 1;
		
	}
	
	int currentSymbol, phraseStartPosition, currentPosition, temp, phraseLength;
	
	phraseStartPosition = 0; /* ftell(inputFile); */
	
	/* fscanf(inputFile, "%d", &cur) != EOF */
	while (1) {
		
		currentSymbol = fgetc(inputFile);
		
		if (currentSymbol == ' ') continue;
		
		if (currentSymbol == '.' || currentSymbol == EOF) {
			
			/* current pharase has ended */
			
			currentPosition = ftell(inputFile);
			
			fseek(inputFile, phraseStartPosition, SEEK_SET);
			
			phraseLength = currentPosition - phraseStartPosition;
			
			char* phrase = (char*)malloc(phraseLength * sizeof(char) + sizeof(char)); /* +1 for null-terminator */
			
			phrase[phraseLength - 1] = '\0';
			
			fread(phrase, sizeof(char), phraseLength, inputFile);
			
			printf("Current phrase (%d): ", phrase[0]);
			puts(phrase);
			
			if (phraseOk(phrase)) {
				
				fwrite(phrase, sizeof(char), phraseLength, tempFile);
				
			}
			
			if (currentSymbol == EOF) break;
			
			fseek(inputFile, currentPosition, SEEK_SET);
			
			phraseStartPosition = currentPosition + 1;
			
			/*do {
				
				temp = fgetc(inputFile);
				
				currentPosition++;
				
			} while (temp != '\n' && temp != EOF);
			
			phraseStartPosition = currentPosition + 1;
			
			fseek(inputFile, phraseStartPosition, SEEK_SET);*/
			
			
		}
		
	}
	
	fclose(inputFile);
	fclose(tempFile);
	
	system("pause");
	
	return 0;
	
}

char phraseOk(char* phrase) {
	
	int d;
	
	if (sscanf(phrase, "%d", &d) || sscanf(phrase, "%d-é", &d)) return 1;
	
	while (*phrase++ != '\0') {
		
		if (*phrase == ' ') {
			
			if (sscanf(phrase, "%d", &d) || sscanf(phrase, "%d-é", &d)) return 1;
			
		}
		
	}
	
	return 0;
	
}
