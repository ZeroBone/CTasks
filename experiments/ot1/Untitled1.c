#include <stdlib.h>
#include <stdio.h>

int main() {
	
	int a = 2;
	
	double x = 1.7;
	
	printf("x=%+-#*.f\na=%5d.1", 10 * a, x, 10 * a);
	
	return 0;
}
