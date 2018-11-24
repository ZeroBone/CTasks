#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_INPUT_LENGTH 50
#define SPACE ' '

void swapFirstLastWords(char* string, int length, const char wordSeparator);
void reverseString(char* string, int start, int end);
void rotateStringLeft(char *string, int length, int amount);
void rotateStringRight(char *string, int length, int amount);
void swapFirstLastStringParts(char* string, int realLength, int firstLength, int lastLength);

int main() {
	
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

void reverseString(char* string, int from, int to) {
    
    while (from < to) {
    	
    	string[from] ^= string[to];
    	string[to] ^= string[from];
    	string[from] ^= string[to];
        
        from++; 
        to--; 
        
    }
    
}

void rotateStringLeft(char *string, int length, int amount) {
	
    reverseString(string, 0, amount - 1);
    
    reverseString(string, amount, length - 1);
    
    reverseString(string, 0, length - 1);
    
}

void rotateStringRight(char *string, int length, int amount) {
	
    reverseString(string, 0, length - 1);
    
    reverseString(string, 0, amount - 1);
    
    reverseString(string, amount, length - 1);
    
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
	int minLength = lastLength < firstLength ? lastLength : firstLength;
	int i, p1, p2;
	
	if (delta > 0) {
		
		/* last fragment is longer than the first one */
		
		p1 = 0;
		p2 = realLength - minLength;
				
	}
	else {
		
		/* first fragment is longer than the last one */
		
		p1 = realLength - minLength;
		p2 = 0;
		
	}
	
	for (i = 0; i < minLength; i++) {
			
		string[p1] ^= string[p2];
		string[p2] ^= string[p1];
		string[p1] ^= string[p2];
		
		p1++;
		p2++;
		
	}
	
	if (delta > 0) rotateStringRight(string, realLength - minLength, delta);
	else rotateStringLeft(string + minLength, realLength - minLength, -delta);
	
}
