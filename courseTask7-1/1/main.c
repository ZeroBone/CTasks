#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <windows.h>
#define MAX_FNAME_LENGTH 50

char isEndOfWord(int c);
char isEndOfPhrase(int c);
char fOk(FILE* file);

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
	char hasMama = 0, wordBegan = 1, phraseEnded = 0;
	
	while (1) {
		
		if (phraseEnded) {

			currentPosition = ftell(file);
			
			fseek(file, phraseStart, SEEK_SET);
			
			do {
				
				temp = fgetc(file);
				
				if (temp != EOF) {
					
					if (!hasMama) fputc(temp, tempFile);
				
					/*printf("%c", temp);*/
					
				}
				
			} while (temp != EOF && ftell(file) < currentPosition);
			
			/*fputc('|', tempFile);*/
			
			/*printf("\n");*/
			
			fseek(file, currentPosition, SEEK_SET);
			
			if (current == EOF) break;
			
			/* reset */
			
			phraseEnded = 0;
			hasMama = 0;
			phraseStart = currentPosition;
			wordBegan = 1;
			
		}
		else if (hasMama) {
			
			/* skip everything */
			
			do {
				
				current = fgetc(file);
				
			} while (!isEndOfPhrase(current));
			
			phraseEnded = 1;
			
			continue;
			
		}
		
		if (wordBegan && fOk(file)) {
			
			current = fgetc(file);
		
			if (isEndOfPhrase(current)) {
				
				phraseEnded = 1;
			
				hasMama = 1;
				
				continue;
				
			}
			
			if (isEndOfWord(current)) {
				
				hasMama = 1;
				
				/*wordBegan = 1;*/
				
				continue;
				
			}
			
		}
		
		wordBegan = 0;
		
		current = fgetc(file);
		
		if (isEndOfPhrase(current)) {
			
			phraseEnded = 1;
			
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

char isEndOfWord(int c) {
	
	return c == ' ' || c == ',' || c == '\n';
	
}

char isEndOfPhrase(int c) {
	
	return c == '.' || c == EOF;
	
}

char fOk(FILE* file) {
	
	static char mama[5];
	
	size_t bytesRead = fread(mama, sizeof(char), 4, file);
	mama[4] = '\0';
	
	/*printf("Mama: ");
	puts(mama);
	puts("===");*/
	
	char isMama = !strcmp(mama, "мама");
	
	if (isMama) return isMama;
	
	fseek(file, -bytesRead, SEEK_CUR);
	
	return 0;
	
}
