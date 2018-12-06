#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <windows.h>
#include <string.h>
#define MAX_FNAME_LENGTH 50
#define MAX_STUDENT_LAST_NAME_LENGTH 20

struct ZString {
	unsigned long int length;
	char* str;
};

int mainMenu();
unsigned char readMark();
char markValid(unsigned char mark);
int fileViewMenu(FILE *file);
void writeZString(FILE *file, struct ZString *str);
void toZString(char* str, struct ZString *zString);

struct Student {
	struct ZString name;
	unsigned char marks[3];
};

int main(int argc, char *argv[]) {
	
	setlocale(LC_ALL, "Russian");
	
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	
	puts("Welcome!");
	
	while (mainMenu() == 1);
	
	system("pause");
	
	return 0;
	
}

int mainMenu() {
	
	puts("Please enter a number below to select what you want to do:");
	puts("1 - create new exam results file.");
	puts("2 - view the exam results file.");
	puts("3 - exit the program.");
	
	int result;
	
	scanf("%d", &result);
	fgetc(stdin);
	
	switch (result) {
		
		case 1:
			
			/* new file */
			
			puts("Enter output file name:");
			
			char outputFileName[MAX_FNAME_LENGTH];
			
			fgets(outputFileName, MAX_FNAME_LENGTH, stdin);
	
			outputFileName[strlen(outputFileName) - 1] = '\0';
			
			FILE *outputFile;
			
			puts(outputFileName);
			
			if ((outputFile = fopen(outputFileName, "wb")) == NULL) {
				
				perror("An error occurred while trying to open the output file for writing");
				
				return 1;
				
			}
			
			int studentCount = 0;
			
			fwrite(&studentCount, sizeof(int), 1, outputFile);
			
			fclose(outputFile);
			
			puts("File successfully created.");
			
			return 1;
			
		case 2:
			
			/* view & edit file */
			
			puts("Enter file name:");
	
			char fileName[MAX_FNAME_LENGTH];
			
			fgets(fileName, MAX_FNAME_LENGTH, stdin);
			fileName[strlen(fileName) - 1] = '\0';
			
			FILE *file;
			
			if ((file = fopen(fileName, "rb")) == NULL) {
				
				perror("An error occurred while trying to file for reading");
				
				return 1;
				
			}
			
			while (fileViewMenu(file) == 1);
			
			fclose(file);
			
			break;
			
		case 3:
			return 0;
			
		default:
			
			puts("The number you entered doesn't correspond to any of the menu items. Please try again.");
			
			return 1;
		
	}
	
	return 0;
	
}

int fileViewMenu(FILE *file) {
	
	puts("Please enter a number below to select what you want to do:");
	puts("1 - view file.");
	puts("2 - add exam result.");
	puts("3 - delete an exam result.");
	puts("4 - edit an exam result.");
	puts("5 - get the amount of 2-s for every discipline.");
	puts("6 - get students, that have 2-s for in least 1 exam.");
	puts("7 - return to the main menu.");
	
	int result;
	
	scanf("%d", &result);
	fgetc(stdin);
	
	switch (result) {
		
		case 2:
			
			puts("Enter student last name:");
			
			char studentLastName[MAX_STUDENT_LAST_NAME_LENGTH];
			fgets(studentLastName, MAX_STUDENT_LAST_NAME_LENGTH, stdin);
			studentLastName[strlen(studentLastName) - 1] = '\0';
			
			struct Student student;
			
			puts("Enter the mark for physics:");
			while (!markValid(student.marks[0] = readMark())) puts("Invalid mark entered, try again:");
			
			puts("Enter the mark for math:");
			while (!markValid(student.marks[1] = readMark())) puts("Invalid mark entered, try again:");
			
			puts("Enter the mark for informatics:");
			while (!markValid(student.marks[2] = readMark())) puts("Invalid mark entered, try again:");
			
			toZString(studentLastName, student.name);
			
			return 1;
		
		default:
			
			puts("Invalid menu item selected, try again.");
			
			return 1;
		
	}
	
	return 0;
	
}

char markValid(unsigned char mark) {
	
	return mark >= 2 && mark <= 5;
	
}

unsigned char readMark() {
	
	int temp;
	
	scanf("%d", &temp);
	
	return (unsigned char)temp;
	
}

void writeZString(FILE *file, struct ZString *str) {
	
	fwrite(&str->length, sizeof(long int), 1, file);
	
	fwrite(str->str, sizeof(char), str->length, file);
	
}

void toZString(char* str, struct ZString *zString) {
	
	zString->length = (unsigned long int)strlen(str) - 1;
	
	zString->str = str;
	
}
