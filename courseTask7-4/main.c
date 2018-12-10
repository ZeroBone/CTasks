#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <windows.h>
#include <string.h>
#define MAX_FNAME_LENGTH 50
#define MAX_STUDENT_LAST_NAME_LENGTH 20
#define STUDENT_COMPONENT_LENGTH 27
#define STUDENTS_PER_PAGE 5
#define MARK_MIN 2
#define MARK_MAX 5
#define MARK_TWO 2

struct Student {
	char* name;
	unsigned char marks[3];
};

int mainMenu();
unsigned char readMark();
char markValid(unsigned char mark);
int fileViewMenu(char *fileName);
void writeStudent(FILE *file, struct Student *student);
void fwriteString(FILE *file, char *string);
char* freadString(FILE *file, unsigned int maxLength);
struct Student readStudent(FILE *file);
void writeInt(FILE *file, long int value);

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
			
			if ((outputFile = fopen(outputFileName, "wb")) == NULL) {
				
				perror("An error occurred while trying to open the output file for writing");
				
				return 1;
				
			}
			
			writeInt(outputFile, 0); /* student count */
			
			fclose(outputFile);
			
			system("CLS");
			
			puts("File successfully created.");
			
			break;
			
		case 2:
			
			/* view & edit file */
			
			puts("Enter file name:");
	
			char fileName[MAX_FNAME_LENGTH];
			
			fgets(fileName, MAX_FNAME_LENGTH, stdin);
			fileName[strlen(fileName) - 1] = '\0';
			
			system("CLS");
			
			while (fileViewMenu(fileName) == 1);
			
			break;
			
		case 3:
			return 0;
			
		default:
			
			system("CLS");
			
			puts("The number you entered doesn't correspond to any of the menu items. Please try again.");
			
			return 1;
		
	}
	
	return 1;
	
}

int fileViewMenu(char *fileName) {
	
	FILE *file;
	
	puts("Please enter a number below to select what you want to do:");
	puts("1 - view file.");
	puts("2 - add exam result.");
	puts("3 - delete an exam result.");
	puts("4 - edit an exam result.");
	puts("5 - get the amount of 2-s for every discipline.");
	puts("6 - get students, that have 2-s for at least 1 exam.");
	puts("7 - return to the main menu.");
	
	int result;
	
	scanf("%d", &result);
	fgetc(stdin);
	
	switch (result) {
		
		case 1:
			
			/* view file */
			
			if ((file = fopen(fileName, "rb")) == NULL) {
		
				perror("An error occurred while trying to open the file for reading");
				
				return 1;
				
			}
			
			long int totalCount;
			
			fseek(file, 0, SEEK_SET);
			
			fread(&totalCount, sizeof(long int), 1, file);
			
			if (!totalCount) {
				
				system("CLS");
				
				puts("File empty, nothing to view.");
				
				break;
				
			}
			
			long int offset = 0, i;
			long int studentsPerPage = STUDENTS_PER_PAGE > totalCount ? totalCount : STUDENTS_PER_PAGE;
			int choise;
			struct Student stud;
			
			printf("Student per page: %d\n", studentsPerPage);
			
			while (1) {
				
				system("CLS");
				
				for (i = 0; i < studentsPerPage; i++) {
					
					fseek(file, sizeof(long int) + ((offset + i) * STUDENT_COMPONENT_LENGTH), SEEK_SET);
					
					/*printf("Physics mark: %d\n", fgetc(file));
					printf("Math mark: %d\n", fgetc(file));
					printf("inf mark: %d\n", fgetc(file));*/
					
					stud = readStudent(file);
					
					printf("Student last name: ");
					puts(stud.name);
					printf("Physics mark: %d\n", stud.marks[0]);
					printf("Math mark: %d\n", stud.marks[1]);
					printf("Informatics mark: %d\n", stud.marks[2]);
					
				}
				
				puts("Which direction do you want to scroll to?");
				puts("1 - scroll up.");
				puts("2 - scroll down.");
				puts("3 - exit.");
				
				scanf("%d", &choise);
				
				switch (choise) {
					
					case 1:
						/* scroll up */
						
						offset -= studentsPerPage;
						if (offset < 0) offset = 0;
						
						break;
						
					case 2:
						/* scroll down */
						offset += studentsPerPage;
						if (offset > totalCount - studentsPerPage) offset = totalCount - studentsPerPage;
						
						break;
					
					default:
						goto exitMark;
					
				}
				
			}
			exitMark:
			
			system("CLS");
			
			break;
		
		case 2:
			
			system("CLS");
			
			if ((file = fopen(fileName, "wb")) == NULL) {
		
				perror("An error occurred while trying to open the file for writing");
				
				return 1;
				
			}
			
			/* add exam result */
			
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
			
			student.name = studentLastName;
			
			long int studentCount = 0;
			fread(&studentCount, sizeof(long int), 1, file);
			
			fseek(file, 0, SEEK_SET);
			
			writeInt(file, studentCount + 1);
			
			fseek(file, sizeof(long int) + (studentCount * STUDENT_COMPONENT_LENGTH), SEEK_SET);
			
			writeStudent(file, &student);
			
			fclose(file);
			
			puts("Exam result added.");
			
			break;
			
		case 3:
			/* delete an exam result */
			
			system("CLS");
			
			if ((file = fopen(fileName, "wb")) == NULL) {
		
				perror("An error occurred while trying to open the file for writing");
				
				return 1;
				
			}
			
			/* TODO */
			
			break;
			
		case 7:
			
			system("CLS");
			
			return 0;
		
		default:
			
			system("CLS");
			
			puts("Invalid menu item selected, try again.");
			
			break;
		
	}
	
	return 1;
	
}

char markValid(unsigned char mark) {
	
	return mark >= MARK_MIN && mark <= MARK_MAX;
	
}

unsigned char readMark() {
	
	int temp;
	
	scanf("%d", &temp);
	
	return (unsigned char)temp;
	
}

void writeStudent(FILE *file, struct Student *student) {
	
	fputc(student->marks[0], file);
	fputc(student->marks[1], file);
	fputc(student->marks[2], file);
	
	fwriteString(file, student->name);
	
}

void fwriteString(FILE *file, char *string) {
	
	while (*string != '\0') {
		
		fputc(*string, file);
		
		string++;
		
	}
	
	fputc(0, file);
	
}

char* freadString(FILE *file, unsigned int maxLength) {
	
	char str[maxLength];
	unsigned int i;
	int current;
	
	for (i = 0; i < maxLength; i++) {
		
		current = fgetc(file);
		
		if (current == 0 || current == EOF) {
			
			str[i] = '\0';
			
			break;
			
		}
		
		str[i] = current;
		
	}
	
	return str;
	
}

struct Student readStudent(FILE *file) {
	
	struct Student student;
	
	student.marks[0] = (unsigned char)fgetc(file);
	student.marks[1] = (unsigned char)fgetc(file);
	student.marks[2] = (unsigned char)fgetc(file);
	
	student.name = freadString(file, MAX_STUDENT_LAST_NAME_LENGTH);
	
	return student;
	
}

void writeInt(FILE *file, long int value) {
	
	fwrite(&value, sizeof(long int), 1, file);
	/*unsigned long int uvalue = (unsigned long int)value;
	
	fputc((uvalue >> 24) & 0xff, file);
	fputc((uvalue >> 16) & 0xff, file);
	fputc((uvalue >> 8) & 0xff, file);
	fputc(uvalue & 0xff, file);*/
	
}
