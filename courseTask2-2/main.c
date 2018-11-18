#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/*
x = 1, res = 0.903362
x = 100000, res = ------
x = 100001, res = 1.348566

*/

double ctg(double value) {
       
    return cos(value) / sin(value);       
       
}

double s(double x) {
       
    double numeratorEl1 = fabs(
        pow(log10(ctg(x)), 2) -
        (
        (pow(3 * x, .25)) / /* numerator */
        (cos(x))   /* denominator */
        )
    );
    
    double numeratorEl2 = sqrt(1 / (2 * x));
    
    double numerator = sqrt(numeratorEl1 + numeratorEl2 + 1);
    
    double denominator = exp(-3 * x) + exp(atan(x));
    
    return numerator / denominator;
    
}

int main() {
    
    double x;
    
    printf("x = ");
    
    scanf("%lf", &x);
    
    printf("Input: x = %lf\n", x);
    
    if (fabs(sin(x)) < 1e-5 || ctg(x) < 1e-5 || x < 1e-5) {
    	
    	printf("Invalid x input. s is not defined in this point.");
    	
    	system("pause");
    	
    	return 0;
    	
	}
    
    double result = s(x);
    
    printf("f = %lf\n", result);
  
    system("pause");
    	
    return 0;
    
}
