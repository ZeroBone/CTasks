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

const char *tempFileName = "temp.txt";

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
	
	if ((tempFile = fopen(tempFileName, "w")) == NULL) {
		
		perror("An error occurred while trying to create a temp file");
		system("pause");
		return 2;
		
	}
	
	int current, temp, phraseStart = 0, currentPosition;
	char hasNumbers = 0, wordBegan = 1, phraseEnded = 0;
	
	while (1) {
		
		if (phraseEnded) {

			currentPosition = ftell(file);
			
			/*printf("Current: %d As char: %c\n", current, current);
			
			printf("CURRENT POSITION: %d\n", currentPosition);*/
			
			if (hasNumbers) puts("PHRASE WITH NUMBER(S):");
			else puts("PHRASE WITHOUT ANY NUMBER:");
			
			fseek(file, phraseStart, SEEK_SET);
			
			do {
				
				temp = fgetc(file);
				
				if (temp != EOF) {
					
					if (hasNumbers) fputc(temp, tempFile);
				
					printf("%c", temp);
					
				}
				
			} while (temp != EOF && ftell(file) < currentPosition);
			
			/* fputc('|', tempFile); */
			
			printf("\n");
			
			fseek(file, currentPosition, SEEK_SET);
			
			if (current == EOF) break;
			
			/*printf("Next: '%c'\n", fgetc(file));
			fseek(file, currentPosition, SEEK_SET);*/
			
			/* reset */
			
			phraseEnded = 0;
			hasNumbers = 0;
			phraseStart = currentPosition;
			wordBegan = 1;
			
		}
		else if (hasNumbers) {
			
			/* skip everything */
			
			do {
				
				current = fgetc(file);
				
			} while (!isEndOfPhrase(current));
			
			phraseEnded = 1;
			
			continue;
			
		}
		
		if (wordBegan && freadInt(file, &temp)) {
			
			current = fgetc(file);
			
			printf("Detected number %d before %c\n", temp, current);
		
			if (isEndOfPhrase(current)) {
				
				phraseEnded = 1;
			
				hasNumbers = 1;
				
				continue;
				
			}
			
			if (isEndOfWord(current)) {
				
				hasNumbers = 1;
				
				/*wordBegan = 1;*/
				
				continue;
				
			}
			
			temp = current;
			current = fgetc(file);
			
			if (isEndOfPhrase(current)) {
				
				phraseEnded = 1;
				
				continue;
				
			}
			
			/* printf("SEQUENCE %c%c DIGITS: %d %d\n", temp, current, temp, current); */
			
			if (temp == '-' && current == 233) { /* 233 is the code of the russian letter */
			
				current = fgetc(file);
				
				if (isEndOfWord(current)) {
				
					hasNumbers = 1;
					
					/*wordBegan = 1;*/
					
					continue;
					
				}
				
				if (isEndOfPhrase(current)) {
					
					hasNumbers = 1;
					
					/*wordBegan = 1;*/
				
					phraseEnded = 1;
					
					continue;
					
				}
				
			}
			
		}
		
		wordBegan = 0;
		
		current = fgetc(file);
		
		/*printf("Read %d (%c) Position: %d Feof: %d\n", current, current, ftell(file), feof(file));*/
		
		if (isEndOfPhrase(current)) {
			
			phraseEnded = 1;
			
			/*current = fgetc(file);*/
			
			continue;
			
		}
		
		if (isEndOfWord(current)) {
			
			wordBegan = 1;
			
		}
		
	}
	
	fclose(file);
	fclose(tempFile);
	
	unlink(inputFileName);
	rename(tempFileName, inputFileName);
	
	system("pause");
	
	return 0;
	
}

void fprintFragment(FILE *file, int count) {
	
	int i;
	
	for (i = 0; i < count; i++) {
		
		fputc(fgetc(file), stdout);
		
	}
	
	fseek(file, -count, SEEK_CUR);
	
}

char isEndOfWord(int c) {
	
	return c == ' ' || c == ',' || c == '\n';
	
}

char isEndOfPhrase(int c) {
	
	return c == '.' || c == EOF;
	
}

char freadInt(FILE* file, int *destination) {
	
	int current = fgetc(file);
	
	if (current == EOF) {
		
		/*fseek(file, -1, SEEK_CUR);*/ /* this was the problem */
		
		return 0;
	
	}
	
	if (current == '+') {
		
		if (!freadNumber(file, destination)) {
			
			fseek(file, -1, SEEK_CUR);
			
			return 0;
			
		}
		
		return 1;
		
	}
	
	if (current == '-') {
		
		if (!freadNumber(file, destination)) {
			
			fseek(file, -1, SEEK_CUR);
			
			return 0;
			
		}
		
		*destination = -*destination;
		
		return 1;
		
	}
	
	fseek(file, -1, SEEK_CUR);
	
	return freadNumber(file, destination);
	
}

char freadNumber(FILE *file, int *destination) {
	
	int current = fgetc(file);
	
	if (current == EOF || current < '0' || current > '9') {
	
		fseek(file, -1, SEEK_CUR);
	
		return 0;
	
	}
	
	int result = 0;
	
	do {
		
		result = (result * 10) + (current - '0');
		
	} while ((current = fgetc(file)), current != EOF && current >= '0' && current <= '9');
	
	*destination = result;
	
	fseek(file, -1, SEEK_CUR);
	
	return 1;
	
}

