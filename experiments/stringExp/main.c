#include <stdio.h>
#include <stdlib.h>

void test(char*);

int main() {
	
	char str = {'a', 'b', 'c'}; /* this is not a string */
	char s1[] = {'a', 'b', 'c', '\0'};
	char s2[10] = {'a', 'b', 'c'};
	char s3[] = {67, 68, 69, 0}; /* ASCII codes */
	
	char s4[] = "abc";
	char s5[10] = "abc"; /* the rest is filled with zero-bytes */
	
	char *s6 = "abc";
	
	printf("Char: %c\n", s6[0]);
	
	/* modifications */
	s4[0] = 'x';
	test(s4);
	
	printf("S4 PASS\n");
	
	/* s6[0] = 'x'; (Will lead to a Runtime error) */
	/* *s6 = 1; (Will lead to a Runtime error) */
	/* *(s6 + 1) = 'd'; (Will lead to a Runtime error) */
	/* test(s6); (Will lead to a Runtime error) */
	
	/* s4 = "xyz"; (Syntax error, attempt to alter a constant) */
	s6 = "xyz"; /* pointer changed */
	
	system("pause");
	return 0;
	
}

void test(char *str) {
	
	str[0] = str[1];
	
}
