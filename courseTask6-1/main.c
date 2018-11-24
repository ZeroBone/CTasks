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
	
	swapFirstLastWords(str, stringLength, SPACE);
	
	printf("New string: ");
	puts(str);
	
	system("pause");
	
	return 0;
	
}

void swapFirstLastWords(char* string, int length, const char wordSeparator) {
	
	int firstWordLength = 0;
	
	while (string[firstWordLength] != wordSeparator && string[firstWordLength + 1] != '\0') firstWordLength++;
	
	printf("First word length: %d\n", firstWordLength);
	
	int lastWordLength = 0;
	
	while (string[length - 2 - lastWordLength] != wordSeparator && length - 1 - lastWordLength > 0) lastWordLength++;
	
	printf("Last word length: %d\n", lastWordLength);
	
	swapFirstLastStringParts(string, length - 1, firstWordLength, lastWordLength);
	
}

void swapFirstLastStringParts(char* string, int realLength, int firstLength, int lastLength) {
	
	if (firstLength + lastLength > realLength) {
		
		/* the regions are overlapping, we cannot swap safely */
		
		return;
		
	}
	
	if (firstLength == lastLength) {
		/* we are lucky, no need to shift char's */
		
		int i, parallelIndex;
		for (i = 0; i < firstLength; i++) {
			
			parallelIndex = realLength - firstLength + i;
			
			/*
			if i = parallelIndex we cannot use this xor-based swapping, cause we will xor the value with it self.
			but because we checked that the regions don't overlap we can do this in this case.
			anyway, swapping any value with it self doesn't make any sense.
			*/
			
			string[i] ^= string[parallelIndex];
			string[parallelIndex] ^= string[i];
			string[i] ^= string[parallelIndex];
			
		}
		
		return;
		
	}
	
	int delta = lastLength - firstLength;
	int i;
	int middleLength = realLength - lastLength - firstLength;
	
	/*
	first we need to copy the part of the fragment with the minimum length
	then we need to shift the middle part to the right by delta (obviously, delta can be negative)
	*/
	
	if (delta > 0) {
		
		/*
		last fragment is longer than the first one
		so we need to copy the first fragment to the end of the string and
		then copy first delta char's of last fragment to the beginning of the string
		*/
		
		for (i = 0; i < firstLength; i++) {
			
			string[length - 1 - firstLength + i] ^= string[i];
			string[i] ^= string[length - 1 - firstLength + i];
			string[length - 1 - firstLength + i] ^= string[i];
			
		}
		
		for (i = 0; i < delta; i++) {
			
			string[i] = string[length - 1 - lastLength + i];
			
		}
		
		/* take the delimiter before the last fragment to figure out, what is placed between words*/
		string[length - 2 - firstLength] = string[length - 2 - lastLength];
		
		for (i = 0; i < middleLength; i++) {
			
			string[firstLength + middleLength + 1 + i] = string[firstLength + 1 + i];
			string[firstLength + 1 + i] = ' ';
			
		}
		
	}
	
}
