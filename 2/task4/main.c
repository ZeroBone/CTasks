#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double f(int n, double x) {
       
    double result = 0;
    
    double sinx = sin(x);
    
    int i;
    
    for (i = 0; i < n; i++) {
        
        double currentExpression = sinx;
        
        short int flag = 1; /* 1 means cos, 0 means sin */
        
        int j;
        
        for (j = 0; j < i; j++) {
            
            currentExpression = flag ? cos(currentExpression) : sin(currentExpression);
            
            flag = flag ? 0 : 1;
                
        }
        
        result += currentExpression;
        
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
