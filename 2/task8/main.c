#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double f(double x, double epsilon) {
	
	double result = x;
	
	long int n = 1;
	
	double currentElement;
	
	do {
		
		double currentElementDenominator = (2 * n) + 1;
		
		/* if we raise -1 to the the even power, it will be 1, in any other case it will not change itself */
		double currentElementNumerator = ((n % 2 == 0) ? 1 : -1) * pow(x, currentElementDenominator);
		
		currentElement = currentElementNumerator / currentElementDenominator;
		
		result += currentElement;
		
		n++;
		
	} while (abs(currentElement) > epsilon);
	
	return result;
	
}

int main(int argc, char *argv[]) {
	
	double epsilon = 1e-5;
	
	double x;
	
	printf("Enter x: ");
	
	scanf("%lf", &x);
	
	printf("x = %lf\n", x);
	
	if (pow(x, 2) >= 1) {
		
		printf("x to the power of 2 should be less than 2!\n");
		
		system("pause");
	
		return 0;
		
	}
	
	double regularResult = f(x, epsilon);
	
	printf("f(x) = %lf\n", regularResult);

	printf("Arctg(x) = %lf\n", atan(x));
	
	system("pause");
	
	return 0;
	
}