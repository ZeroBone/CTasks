#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/*
n = 2, x = 0, res = 1
n = 3, x = 0, res = 1.841471
n = 1000, x = 20, res = 1.879890
*/

double f(int n, double x) {
	
	double result = sin(x);
	
	char flag = 1;
	
	int i;
	
	for (i = 1; i < n; i++) {
		
		result += flag ? cos(result) : sin(result);
		
		flag = !flag;
		
	}
	
	return result;
	
}

int main() {
    
    int n;
    double x;
    
    printf("Enter n: ");
    scanf("%d", &n);

    printf("Enter x: ");
    scanf("%lf", &x);
    
    printf("Data received: n = %d, x = %lf\n\n", n, x);
    
    printf("Result: %lf\n", f(n, x));
    
    system("pause");	
    
    return 0;
    
}
