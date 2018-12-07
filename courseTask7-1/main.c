#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <windows.h>
#define MAX_FNAME_LENGTH 50

void fprintFragment(FILE *file, int count);
char isEndOfWord(int c);
char isEndOfPhrase(int c);
char freadInt(FILE* file, int *destination);
char freadNumber(FILE *file, int *destination);

int main(int argc, char *argv[]) {
	
	setlocale(LC_ALL, "Russian");
	
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	
	char inputFileName[MAX_FNAME_LENGTH];
	
	if (argc < 2) {
		
		printf("Enter input file name:\n");
		
		fgets(inputFileName, MAX_FNAME_LENGTH, stdin);
		inputFileName[strlen(inputFileName) - 1] = '\0';
		
	}
	else {
		
		strcpy(inputFileName, argv[1]);
		
	}
	
	printf("Input file: ");
	puts(inputFileName);
	
	FILE *file, *tempFile;
	
	if ((file = fopen(inputFileName, "r")) == NULL) {
		
		perror("An error occurred while trying to read the file");
		
		system("pause");
		
		return 1;
		
	}
	
	if ((tempFile = fopen("temp.txt", "w")) == NULL) {
		
		perror("An error occurred while trying to create a temp file");
		
		system("pause");
		
		return 2;
		
	}
	
	int phraseStart = 0, phraseEnd = 0;
	char hasNumbers = 0, numberAfterSpace = 0;
	int current, temp;
	char starting = 1, ending[3] = {'?', '?'};
	
	while (1) {
		
		current = fgetc(file);
		
		printf("   Current: %c\n", current);
		
		if (isEndOfPhrase(current)) { /* current == '.' || current == EOF */
			
			phraseEnd = ftell(file);
			
			printf("End of phrase started: %d Reached: %d\n", phraseStart, phraseEnd);
			
			printf("DEBUG: %d\n", ftell(file));
			
			fseek(file, phraseStart, SEEK_SET);
				
			fprintFragment(file, phraseEnd - phraseStart);
			
			printf("DEBUG A: %d\n", ftell(file));
			
			phraseStart = phraseEnd + 1;
				
			if (hasNumbers) {
				
				puts("PHRASE HAS NUMBERS:");
				
			}
			else {
				
				printf("Hasn't got numbers, cur char: %c\n", current);
				
			}
			
			if (current == EOF) break;
			
			hasNumbers = 0;
			starting = 1;
			
		}
		else if (starting || (!hasNumbers && isEndOfWord(current))) {
			
			if (starting) {
				
				fseek(file, -1, SEEK_CUR);
				
				starting = 0;
				
			}
			
			/* end of word, probably start of the new one */
			
			if (freadInt(file, &temp)) {
				
				current = fgetc(file);
				
				printf("Int read: %d Current char: %c\n", temp, current);
				
				if (isEndOfWord(current)) {
					
					/* fseek(file, -1, SEEK_CUR); */
					
					hasNumbers = 1;
					
				}
				else if (isEndOfPhrase(current)) {
					
					hasNumbers = 1;
					
					fseek(file, -1, SEEK_CUR);
					
				}
				else {
					
					fseek(file, -1, SEEK_CUR);
					
					temp = fread(ending, sizeof(char), 2, file);
					
					/* printf("READ %d BYTES ASSUMING -\n", temp); */
					puts(ending);
					
					fseek(file, -1, SEEK_CUR);
					
					if (temp == 2 && strcmp(ending, "-é") == 0) hasNumbers = 1;
					
				}
				
			}
			
		}
		
	}
	
	fclose(file);
	fclose(tempFile);
	
	/* unlink(inputFileName);
	rename("temp.txt", inputFileName); */
	
	system("pause");
	
	return 0;
	
}

void fprintFragment(FILE *file, int count) {
	
	for (; count > 0; count--) {
		
		fputc(fgetc(file), stdout);
		
	}
	
}

char isEndOfWord(int c) {
	
	return c == ' ' || c == ',' || c == '\n';
	
}

char isEndOfPhrase(int c) {
	
	return c == '.' || c == EOF;
	
}

char freadInt(FILE* file, int *destination) {
	
	int current = fgetc(file);
	
	if (current == EOF) return 0;
	
	if (current == '+') return freadNumber(file, destination);
	
	if (current == '-') {
		
		char res = freadNumber(file, destination);
		
		*destination = -*destination;
		
		return res;
		
	}
	
	fseek(file, -1, SEEK_CUR);
	
	return freadNumber(file, destination);
	
}

char freadNumber(FILE *file, int *destination) {
	
	int current = fgetc(file);
	
	if (current == EOF || current < '0' || current > '9') return 0;
	
	int result = 0;
	
	do {
		
		result = (result * 10) + (current - '0');
		
	} while ((current = fgetc(file)), current != EOF && current >= '0' && current <= '9');
	
	*destination = result;
	
	fseek(file, -1, SEEK_CUR);
	
	return 1;
	
}

