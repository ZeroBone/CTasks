#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int factorial(int n) {
	
	if (n > 1) {
		
		return n * factorial(n - 1);
		
	}
	
	return 1;
	
}

double f(double x, double epsilon) {
	
	double result = 1;
	
	int n = 2; /* 0 */
	
	double currentElement;
	
	double factorialValue = 1;
	
	do {
        
        factorialValue *= (n - 1) * n;
        
        /* printf("factorial = %lf\n", factorialValue); */
                
        printf("n: %d Factorials: %lf = %d\n", n, factorialValue, factorial(n));
		
		/* currentElement = pow(x, n) / (double)factorial(n); */
		currentElement = pow(x, n) / factorialValue;
		
		result += currentElement;
		
		n += 2;
		
	} while (fabs(currentElement) > epsilon);
	
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
