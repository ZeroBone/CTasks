#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <windows.h>
#include <string.h>
#define MAX_FNAME_LENGTH 50
#define MAX_STUDENT_LAST_NAME_LENGTH 20
#define STUDENT_COMPONENT_LENGTH 23
#define MARK_MIN 2
#define MARK_MAX 5
#define MARK_TWO 2

struct Student {
	char marks[3];
	char name[MAX_STUDENT_LAST_NAME_LENGTH];
};

int mainMenu();
char readMark();
void inputStudent(struct Student *student);
void tableTop();
void tableStudent(long number, struct Student *stud);
void tableBottom();
char markValid(char mark);
int fileViewMenu(char *fileName);
void writeStudent(FILE *file, struct Student *student);
char readStudent(FILE *file, struct Student *student);
unsigned long fwriteString(FILE *file, char *string);
void freadString(FILE *file, char *str, unsigned int maxLength);
void writeInt(FILE *file, long int value);
int twosForAtLeast1Exam(char *fileName);
int deleteExamResult(char *fileName);

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
	
	getchar();
	
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
			
			/* writeInt(outputFile, 0); */ /* student count */
			
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
	
	if ((file = fopen(fileName, "rb")) == NULL) {
				
		system("CLS");

		perror("FS error");
		
		return 0;
		
	}
	
	fclose(file);
	
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
	getchar();
	
	switch (result) {
		
		case 1:
			
			/* view file */
			
			if ((file = fopen(fileName, "rb")) == NULL) {
				
				system("CLS");
		
				perror("An error occurred while trying to open the file for reading");
				
				return 1;
				
			}
			
			fseek(file, 0, SEEK_SET);
			
			long int offset = 0, i, studentsPerPage = 5;
			int choise;
			struct Student stud;
			
			while (1) {
				
				system("CLS");
				
				fseek(file, offset * STUDENT_COMPONENT_LENGTH, SEEK_SET);
				
				if (!readStudent(file, &stud)) {
					
					if (!offset) {
						
						puts("File empty, nothing to view.");
						
					}
					else {
						
						puts("Nothing to view.");
						
					}
					
					goto exitMark;
					
				}
				
				tableTop();
				
				for (i = 0; i < studentsPerPage; i++) {
					
					fseek(file, (offset + i) * STUDENT_COMPONENT_LENGTH, SEEK_SET);
					
					if (!readStudent(file, &stud)) {
						
						fseek(file, 0, SEEK_SET);
					
						break;
						
					}
					
					/*printf("Student last name: ");
					puts(stud->name);
					printf("Physics mark: %d\n", stud->marks[0]);
					printf("Math mark: %d\n", stud->marks[1]);
					printf("Informatics mark: %d\n", stud->marks[2]);*/
					
					tableStudent(i + offset, &stud);
					
				}
				
				tableBottom();
				
				puts("Which direction do you want to scroll to?");
				puts("1 - scroll up.");
				puts("2 - scroll down.");
				puts("3 - exit.");
				
				scanf("%d", &choise);
				
				getchar();
				
				switch (choise) {
					
					case 1:
						/* scroll up */
						
						offset -= studentsPerPage;
						if (offset < 0) offset = 0;
						
						system("CLS");
						
						break;
						
					case 2:
						/* scroll down */
						offset += studentsPerPage;
						
						system("CLS");
						
						break;
					
					default:
						
						system("CLS");
						
						goto exitMark;
					
				}
				
			}
			exitMark:
				
			fclose(file);
			
			break;
		
		case 2:
			
			system("CLS");
			
			if ((file = fopen(fileName, "ab")) == NULL) {
		
				perror("An error occurred while trying to open the file for writing");
				
				return 1;
				
			}
			
			/* add exam result */
			
			struct Student student;
			
			inputStudent(&student);
			
			/*fseek(file, 0, SEEK_SET);*/
			
			/*fseek(file, -1, SEEK_END);*/
			
			/*printf("Writing to %d\n", ftell(file));*/
			
			writeStudent(file, &student);
			
			fclose(file);
			
			puts("Exam result added.");
			
			break;
			
		case 3:
			/* delete an exam result */
			
			return deleteExamResult(fileName);
			
		case 4:
			
			/* edit an exam result */
			
			if ((file = fopen(fileName, "r+b")) == NULL) {
		
				perror("An error occurred while trying to open the file for editing");
				
				return 1;
				
			}
			
			/* fseek(file, 0, SEEK_CUR); */
			
			puts("Enter student last name:");
			
			char studentName[MAX_STUDENT_LAST_NAME_LENGTH];
			fgets(studentName, MAX_STUDENT_LAST_NAME_LENGTH, stdin);
			studentName[strlen(studentName) - 1] = '\0';
			
			system("CLS");
			
			struct Student st;
			long int n = 0, found = 0;
			char yes;
			
			while (1) {
				
				fseek(file, n * STUDENT_COMPONENT_LENGTH, SEEK_SET);
				
				if (!readStudent(file, &st)) {
					
					break;
					
				}
				
				printf("Comp: Read: %s Searching: %s\n", st.name, studentName);
				
				if (!strcmp(st.name, studentName)) {
					
					found++;
					
					system("CLS");
					
					tableTop();
					
					tableStudent(n, &st);
					
					puts("Edit? (y/n)");
					
					do {
						
						yes = getchar();
						
					} while (yes != 'y' && yes != 'Y' && yes != 'n' && yes != 'N');
					
					getchar();
					
					if (yes == 'y' || yes == 'Y') {
						
						inputStudent(&st);
						
						fseek(file, n * STUDENT_COMPONENT_LENGTH, SEEK_SET);
						
						writeStudent(file, &st);
						
						fseek(file, 0, SEEK_CUR); /* to write mode */
						
					}
					
				}
				
				n++;
				
			}
			
			if (n == 0) {
				
				puts("File empty.");
				
			}
			else if (found == 0) {
				
				puts("No matching students found.");
				
			}
			
			fclose(file);
			
			break;
			
		case 5:
			
			/* get the amount of 2-s for every discipline */
			
			if ((file = fopen(fileName, "rb")) == NULL) {
				
				system("CLS");
		
				perror("(2) An error occurred while trying to open the file for reading");
				
				return 1;
				
			}
			
			fseek(file, 0, SEEK_SET);
			
			long int twos[] = {0, 0, 0};
			long int off = 0;
			int k;
			struct Student stu;
			
			while (1) {
				
				fseek(file, off * STUDENT_COMPONENT_LENGTH, SEEK_SET);
				
				if (!readStudent(file, &stu)) {
					
					if (!off) {
						
						puts("File empty, nothing to view.");
						
					}
					
					break;
					
				}
				
				for (k = 0; k < 3; k++) {
					
					if (stu.marks[k] == MARK_TWO) {
						
						twos[k]++;
						
					}
					
				}
				
				off++;
				
			}
			
			printf("Two's for physics: %d\n", twos[0]);
			printf("Two's for math: %d\n", twos[1]);
			printf("Two's for informatics: %d\n", twos[2]);
			
			fclose(file);
			
			break;
			
		case 6:
			
			/* get students, that have 2-s for at least 1 exam */
			
			return twosForAtLeast1Exam(fileName);
		
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

void inputStudent(struct Student *student) {
	
	puts("Enter student last name:");
	
	fgets(student->name, MAX_STUDENT_LAST_NAME_LENGTH, stdin);
	student->name[strlen(student->name) - 1] = '\0';
	
	puts("Enter the mark for physics:");
	while (!markValid(student->marks[0] = readMark())) puts("Invalid mark entered, try again:");
	
	puts("Enter the mark for math:");
	while (!markValid(student->marks[1] = readMark())) puts("Invalid mark entered, try again:");
	
	puts("Enter the mark for informatics:");
	while (!markValid(student->marks[2] = readMark())) puts("Invalid mark entered, try again:");
	
}

void tableTop() {
	
	puts("--------------------------------------");
	puts("|  N|        Name        | P | M | I |");
	puts("--------------------------------------");
	
}

void tableStudent(long number, struct Student *stud) {
	
	printf("|%3d|%-20s| %1d | %1d | %1d |\n",
		number + 1,
		stud->name,
		stud->marks[0],
		stud->marks[1],
		stud->marks[2]
	);
	
}

void tableBottom() {
	
	puts("--------------------------------------");
	
}

char markValid(char mark) {
	
	return mark >= MARK_MIN && mark <= MARK_MAX;
	
}

char readMark() {
	
	int temp;
	
	scanf("%d", &temp);
	
	return temp;
	
}

void writeStudent(FILE *file, struct Student *student) {
	
	fputc(student->marks[0], file);
	fputc(student->marks[1], file);
	fputc(student->marks[2], file);
	
	int written = 3 + fwriteString(file, student->name);
	
	printf("Written: %d\n", written);
	
	for (;written < STUDENT_COMPONENT_LENGTH; written++) {
		
		fputc(0, file);
		
	}
	
}

char readStudent(FILE *file, struct Student *student) {
	
	int current, i;
	
	for (i = 0; i < 3; i++) {
		
		current = fgetc(file);
	
		if (current == EOF) {
			
			return 0;
			
		}
		
		student->marks[i] = current;
		
	}
	
	/*printf("CUROSSTR: %d\n", ftell(file));*/
	
	/*printf("Mark: %d\n", student->marks[0]);
	printf("Mark 2 : %d\n", student->marks[1]);
	printf("Mark 3: %d\n", student->marks[2]);*/
	
	freadString(file, student->name, MAX_STUDENT_LAST_NAME_LENGTH);
	
	return 1;
	
}

unsigned long fwriteString(FILE *file, char *string) {
	
	unsigned long len = 1;
	
	while (*string != '\0') {
		
		fputc(*string, file);
		
		string++;
		
		len++;
		
	}
	
	fputc(0, file);
	
	return len;
	
}

void freadString(FILE *file, char *str, unsigned int maxLength) {
	
	unsigned int i;
	int current;
	
	for (i = 0; i < maxLength; i++) {
		
		current = fgetc(file);
		
		if (current == '\0' || current == EOF) {
			
			str[i] = '\0';
			
			break;
			
		}
		
		str[i] = current;
		
	}
	
}

void writeInt(FILE *file, long int value) {
	
	fwrite(&value, sizeof(long int), 1, file);
	/*unsigned long int uvalue = (unsigned long int)value;
	
	fputc((uvalue >> 24) & 0xff, file);
	fputc((uvalue >> 16) & 0xff, file);
	fputc((uvalue >> 8) & 0xff, file);
	fputc(uvalue & 0xff, file);*/
	
}

int twosForAtLeast1Exam(char *fileName) {
	
	FILE *file;
	
	if ((file = fopen(fileName, "rb")) == NULL) {
				
		system("CLS");

		perror("An error occurred while trying to open the file for reading");
		
		return 1;
		
	}
	
	fseek(file, 0, SEEK_SET);
	
	long int soffset = 0, j, stPerPage = 5;
	int scroll;
	struct Student stu_;
	
	while (1) {
		
		system("CLS");
		
		fseek(file, soffset * STUDENT_COMPONENT_LENGTH, SEEK_SET);
		
		if (!readStudent(file, &stu_)) {
			
			if (!soffset) {
				
				puts("File empty, nothing to view.");
				
			}
			
			goto exitM;
			
		}
		
		tableTop();
		
		j = 0;
		
		while (j < stPerPage) {
			
			fseek(file, (soffset + j) * STUDENT_COMPONENT_LENGTH, SEEK_SET);
			
			if (!readStudent(file, &stu_)) {
				
				fseek(file, 0, SEEK_SET);
			
				break;
				
			}
			
			if (stu_.marks[0] == MARK_TWO || stu_.marks[1] == MARK_TWO || stu_.marks[2] == MARK_TWO) {
				
				tableStudent(j + soffset, &stu_);
				
			}
			
			j++;
			
		}
		
		tableBottom();
		
		puts("Which direction do you want to scroll to?");
		puts("1 - scroll up.");
		puts("2 - scroll down.");
		puts("3 - exit.");
		
		scanf("%d", &scroll);
		
		getchar();
		
		switch (scroll) {
			
			case 1:
				/* scroll up */
				
				soffset -= stPerPage;
				if (soffset < 0) soffset = 0;
				
				system("CLS");
				
				break;
				
			case 2:
				/* scroll down */
				soffset += stPerPage;
				
				system("CLS");
				
				break;
			
			default:
				
				system("CLS");
				
				goto exitM;
			
		}
		
	}
	exitM:
		
	fclose(file);
	
	return 0;
	
}

int deleteExamResult(char *fileName) {
	
	FILE *file;
	FILE *tempFile;
	
	if ((file = fopen(fileName, "r+b")) == NULL) {
		
		perror("An error occurred while trying to open the file for reading");
		
		return 1;
		
	}
	
	if ((tempFile = fopen("temp.bin", "wb")) == NULL) {
		
		perror("An error occurred while trying to open the file for reading");
		
		return 1;
		
	}
	
	/* fseek(file, 0, SEEK_CUR); */
	
	puts("Enter student last name:");
	
	char studentName[MAX_STUDENT_LAST_NAME_LENGTH];
	fgets(studentName, MAX_STUDENT_LAST_NAME_LENGTH, stdin);
	studentName[strlen(studentName) - 1] = '\0';
	
	system("CLS");
	
	struct Student st;
	long int n = 0, found = 0;
	int i;
	char yes;
	char keep = 1;
	
	while (1) {
		
		fseek(file, n * STUDENT_COMPONENT_LENGTH, SEEK_SET);
		
		if (!readStudent(file, &st)) {
			
			break;
			
		}
		
		if (!strcmp(st.name, studentName)) {
			
			found++;
			
			system("CLS");
			
			tableTop();
			
			tableStudent(n, &st);
			
			puts("Delete? (y/n)");
			
			do {
				
				yes = getchar();
				
			} while (yes != 'y' && yes != 'Y' && yes != 'n' && yes != 'N');
			
			getchar();
			
			if (yes == 'y' || yes == 'Y') {
				
				fseek(file, n * STUDENT_COMPONENT_LENGTH, SEEK_SET);
				
				keep = 0;
				
				fseek(file, 0, SEEK_CUR); /* to write mode */
				
			}
			else keep = 1;
			
		}
		else keep = 1;
		
		if (keep) {
			
			writeStudent(tempFile, &st);
			
		}
		
		n++;
		
	}
	
	if (n == 0) {
		
		puts("File empty.");
		
	}
	else if (found == 0) {
		
		puts("No matching students found.");
		
	}
	
	fclose(file);
	fclose(tempFile);
	
	unlink(fileName);
	rename("temp.bin", fileName);
	
	return 0;
	
}
