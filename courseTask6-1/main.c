#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
	
	const char SPACE = ' ';
	
	char str[50];
	
	printf("Enter string:");
	
	/* scanf("%s", &str); */
	gets(str);
	
	/* printf("String: %s\n", str); */
	printf("String: ");
	puts(str);
	
	char* firstSpace = strchr(str, SPACE);
	char* lastSpace = strrchr(str, SPACE);
	
	char *newString = (char*)malloc((strlen(str) + 1) * sizeof(char));
	
	/* strcpy(newString, str); */
	
	char* pointer = newString;
	
	printf("DEBUG: %d\n",  firstSpace - str);
	
	memcpy(newString, lastSpace + 1, str + strlen(str) - lastSpace);
	
	pointer += str + strlen(str) - lastSpace;
	
	/* TODO: fix bug */
	
	if (firstSpace != lastSpace) {
		
		memcpy(pointer, firstSpace + 1, lastSpace - firstSpace);
		
	}
	
	/*while (pointer != firstSpace) {
		
		*pointer++ = *(lastSpace + (pointer - str));
		
	}*/
	
	/* strncat(newString, str, firstSpace - str);*/
	
	printf("New string: ");
	puts(newString);
	
	printf("New string length: %d\n", strlen(newString));
	
	system("pause");
	
	return 0;
	
}
