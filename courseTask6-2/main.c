#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_INPUT_LENGTH 50
#define POINT '.'

/*
Enter string:winter. Has come.it's cold outside.
String: winter. Has come.it's cold outside.

Modified string: winter. Has come.It's cold outside.

=====================

Enter string:.л.е.м.м.а
String: .л.е.м.м.а

Modified string: .Л.Е.М.М.А

=====================

Enter string:электрон, атом. молекула
String: электрон, атом. молекула

Modified string: электрон, атом. Молекула

*/

int main() {
	
	char string[MAX_INPUT_LENGTH];
	
	printf("Enter string:");
	
	/* scanf("%s", &str); */
	fgets(string, MAX_INPUT_LENGTH, stdin);
	
	/* printf("String: %s\n", str); */
	printf("String: ");
	puts(string);
	
	/*printf("TEST а: %c\n", 224);
	printf("а: %d\n", 'а');
	printf("я: %d\n", 'я');*/
	
	char* pointer = string;
	
	while ((pointer = strchr(pointer, POINT)) != NULL) {
		
		pointer++;
		
		if (*(pointer + 1) == '\0') {
			
			break;
			
		} 
		
		while (*pointer == ' ') pointer++;
		
		/* printf("%d\n", *pointer); */
		
		if ((*pointer) >= -96 && (*pointer) <= -17) {
				
			/* printf("Russian letter %c\n", *pointer); */
			
			*pointer = ('А' + (*pointer) - 'а');
			
		}
		else if ((*pointer) >= 'a' && (*pointer) <= 'z') {
			
			*pointer = ('A' + (*pointer) - 'a');
			
		}
		
		/* pointer++; */
		
	}
	
	/*int i = 0;
	char foundPoint = 0;
	
	while (string[i] != '\0') {
		
		printf("Char %c: %d\n", string[i], string[i]);
		
		if (string[i] == ' ') {}
		else if (string[i] == POINT) {
			
			foundPoint = 1;
			
		}
		else if (foundPoint) {
			
			if (string[i] >= -96 && string[i] <= -17) {
				
				printf("Russian letter %c\n", string[i]);
				
				string[i] = ('А' + string[i] - 'а');
				
			}
			else if (string[i] >= 'a' && string[i] <= 'z') {
				
				string[i] = ('A' + string[i] - 'a');
				
			}
			
			foundPoint = 0;
			
		}
		
		i++;
		
	}*/
	
	printf("Modified string: ");
	
	puts(string);
	
	system("pause");
	
	return 0;
	
}
