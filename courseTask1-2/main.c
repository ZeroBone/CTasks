#include <stdio.h>
#include <stdlib.h>

int main() {
    
    int c = 5;
    int d;
    
    double a = 5.;
    double b;
    
    printf("b=");
    scanf("%lf", &b); /* b input */
    printf("d=");
    scanf("%d", &d); /* d input */

    printf("c: %d, d: %d, a: %1f, b: %1f\n", c, d, a, b);
    
    a += b - 2; /* (b - 2) is added to a */
    
    printf("c: %d, d: %d, a: %1f, b: %1f\n", c, d, a, b);  
  
    d += (++c) - a; /* first c is incremented, then a is subtracted from it and the result is added to d */
    
    printf("c: %d, d: %d, a: %1f, b: %1f\n", c, d, a, b);   

    a *= c--; /* a is multiplied by c and then c is decremented */
    
    printf("c: %d, d: %d, a: %1f, b: %1f\n", c, d, a, b);    

    d *= (c /= 2) + (a /= 10) + (--b);
    
    printf("c: %d, d: %d, a: %1f, b: %1f\n\n", c, d, a, b);
    
    system("pause");
    
    return 0;
    
}
