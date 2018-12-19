#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <windows.h>
#define MAX_FNAME_LENGTH 50

void handlePhrase(FILE *file, FILE *outputFile, long phraseStart, int vowelsFound);
char isEndOfPhrase(int c);
char isVowel(char c);

const char *allVowels = "aeiouAEIOU‡ÂËÓÛ˛ˇ¿≈»Œ”ﬁﬂ";

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
	
	int current, phraseStart = 0;
	int vowels = 0;
	char vstring[50] = "";
	char currentVowelStr[] = "?";
	
	do {
		
		current = fgetc(file);
		
		if (isEndOfPhrase(current)) {
			
			/* handle phrase end */
			handlePhrase(file, tempFile, phraseStart, vowels);
			
			/* reset */
			vowels = 0;
			phraseStart = ftell(file);
			vstring[0] = '\0';
			
			continue;
			
		}
		
		if (isVowel(current) && strchr(vstring, current) == NULL) {
			
			currentVowelStr[0] = current;
			strcat(vstring, currentVowelStr);
			
			/*printf("Current vowels (found %d):\n", vowels + 1);
			puts(vstring);*/
			
			if (++vowels >= 4) {
				
				/* skip everything */
			
				do {
					
					current = fgetc(file);
					
				} while (!isEndOfPhrase(current));
				
				/* handle phrase end */
				handlePhrase(file, tempFile, phraseStart, vowels);
				
				/* reset */
				vowels = 0;
				phraseStart = ftell(file);
				vstring[0] = '\0';
				
			}
			
		}
		
	} while (current != EOF);
	
	fclose(file);
	fclose(tempFile);
	
	unlink(inputFileName);
	rename(tempFileName, inputFileName);
	
	system("pause");
	
	return 0;
	
}

void handlePhrase(FILE *file, FILE *outputFile, long phraseStart, int vowelsFound) {
	
	int currentPosition = ftell(file);
	int temp;
			
	fseek(file, phraseStart, SEEK_SET);
	printf("Found %d:\n", vowelsFound);
	
	if (vowelsFound >= 4) {
		
		do {
	
			temp = fgetc(file);
			
			if (temp != EOF) {
				
				fputc(temp, outputFile);
				
				/* putc(temp, stdout); */
				
			}
			
		} while (temp != EOF && ftell(file) < currentPosition);
		
	}
	/*fputc('|', outputFile);*/
	/*printf("\n");*/
	
	fseek(file, currentPosition, SEEK_SET);
	
}

char isEndOfPhrase(int c) {
	
	return c == '.' || c == EOF;
	
}

char isVowel(char c) {
	
	return strchr(allVowels, c) != NULL;
	
}
