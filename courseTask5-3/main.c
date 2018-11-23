#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define N 30

double integral(double start, double end, double n, double (*f)(double));

double f1(double);
double f2(double);

/*

from -2 to 2

f(x) = 1
result: 4.000000

f(x) = x
result: -0.000000

f(x) = |x|
result: 4.000000

*/

int main() {
	
	printf("F1 integral: %lf\n", integral(-2, 2, N, f1));
	printf("F2 integral: %lf\n", integral(0, .5, N, f2));
	
	system("pause");
	
	return 0;
	
}

/* 2 * x + x^2 range: (-2, 2) */
double f1(double x) {
	
	return (2 * x) + (x * x);
	
}

/* 4 * cos^2(x) range: (0, 0.5) */
double f2(double x) {
	
	double cosValue = cos(x);
	
	return 4 * cosValue * cosValue;
	
}

double integral(double start, double end, double splitCount, double (*f)(double)) {
	
	double h = (end - start) / splitCount;
	double x, s;
	
	for (x = start + (h / 2), s = 0; x < end; x += h) {
		
		s += f(x);
		
	}
	
	return s * h;
	
}
