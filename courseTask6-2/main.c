#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_INPUT_LENGTH 50
#define POINT '.'

int main() {
	
	char string[MAX_INPUT_LENGTH];
	
	printf("Enter string:");
	
	/* scanf("%s", &str); */
	fgets(string, MAX_INPUT_LENGTH, stdin);
	
	/* printf("String: %s\n", str); */
	printf("String: ");
	puts(string);
	
	int i = 0;
	char foundPoint = 0;
	
	while (string[i] != '\0') {
		
		if (string[i] == ' ') {}
		else if (string[i] == POINT) {
			
			foundPoint = 1;
			
		}
		else if (foundPoint) {
			
			/*if (strtolower(string[i]) == string[i]) {
				
				string[i] = strtoupper(string[i]);
				
			}*/
			
			if (string[i] < 65 || string[i] > 90) {
				
				string[i] += ('A' - 'a');
				
			}
			
			foundPoint = 0;
			
		}
		
		i++;
		
	}
	
	printf("Modified string: ");
	
	puts(string);
	
	system("pause");
	
	return 0;
	
}
