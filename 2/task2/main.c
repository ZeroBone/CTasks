#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double ctg(double value) {
       
    return cos(value) / sin(value);       
       
}

double s(double x) {
       
    double numeratorEl1 = abs(
        pow(log10(ctg(x)), 2) -
        (
        (pow(3 * x, .25)) / /* numerator */
        (cos(x))   /* denominator */
        )
    );
    
    double numeratorEl2 = sqrt(1 / 2 * x);
    
    double numerator = sqrt(numeratorEl1 + numeratorEl2 + 1);
    
    double denominator = exp(-3 * x) + exp(atan(x));
    
    return numerator / denominator;
}

int main(int argc, char *argv[]) {
    
    double x;
    
    printf("x = ");
    
    scanf("%lf", &x);
    
    printf("Input: x = %lf\n", x);
    
    double result = s(x);
    
    printf("f = %lf\n", result);
  
    system("pause");
    	
    return 0;
    
}
