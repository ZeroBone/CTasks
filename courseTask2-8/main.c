#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/*
x = 0.3, res = 0.308543, arctg = 0.291457
x = 0.001, res = 0.001000, arctg = 0.001000
*/

double f(double x, double epsilon) {
	
	double result = x;
	
	double current = 1;
	
	/* char flag = 1; *//* 1 means minus, 0 means plus */
	
	double xPower = x * x * x;
	
	int n2plus1 = 3;
	
	while (fabs(current) > epsilon) {
		
		/* current = (flag ? -xPower : xPower) / n2plus1; */
		current = xPower / n2plus1;
		
		n2plus1 += 2;
		
		xPower *= -x * x;
		
		/* flag = !flag; */
		
		result += current;
		
	}
	
	return result;
	
}

int main() {
	
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
