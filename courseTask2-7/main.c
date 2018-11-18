#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/*
x = 0.525, res = 1.141007, check = 1.141007
x = 3.56, res = 17.595818, check = 17.595818
x = 1.197, res = 1.806135, check = 1.806135
*/

double f(double x, double epsilon) {
	
	double result = 1;
	
	double previousValue = 1;
	
	int n = 2;
	
	while (fabs(previousValue) > epsilon) {
		
		previousValue *= (x * x / (n * (n - 1)));
		
		result += previousValue;
		
		n += 2;
		
	}
	
	return result;
	
}

double checkingF(double x) {
	
	return (exp(x) + exp(-x)) / 2;
	
}

int main() {
	
	/* printf("Fact 6: %ld\n", factorial(6)); */
	
	double epsilon = 1e-6;
	
	double x;
	
	printf("Enter x: ");
	
	scanf("%lf", &x);
	
	double rowResult = f(x, epsilon);
	
	printf("Infinite row result: %lf\n", rowResult);

	printf("Checking function: %lf\n", checkingF(x));
	
	system("pause");
	
	return 0;
	
}
