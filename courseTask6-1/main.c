#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_INPUT_LENGTH 50

int main() {
	
	const char SPACE = ' ';
	
	char str[MAX_INPUT_LENGTH];
	
	printf("Enter string:");
	
	/* scanf("%s", &str); */
	fgets(str, MAX_INPUT_LENGTH, stdin);
	
	/* printf("String: %s\n", str); */
	printf("String: ");
	puts(str);
	
	int stringLength = strlen(str);
	
	printf("Length: %d\n", stringLength);
	printf("LastChar: %c\n", str[stringLength - 2]);
	
	int firstWordLength = 0;
	
	while (str[firstWordLength] != SPACE && str[firstWordLength + 1] != '\0') firstWordLength++;
	
	printf("First word length: %d\n", firstWordLength);
	
	int lastWordLength = 0;
	
	while (str[stringLength - 2 - lastWordLength] != SPACE && stringLength - 1 - lastWordLength > 0) lastWordLength++;
	
	printf("Last word length: %d\n", lastWordLength);
	
	printf("New string: ");
	puts(str);
	
	system("pause");
	
	return 0;
	
}
