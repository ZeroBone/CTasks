#include <stdio.h>
#include <stdlib.h>

/*
n = -5, res = 0
n = 0, res = 0
n = 25, res = 1
n = 5, res = 1
n = 1, res = 1
*/

char isPowerOf(int x, int power) {
    
    if (x == 1) return 1;
    
    if (x < power) return 0;
    
    /* char isPower = 1; */
    
    while (x > 1) {
        
        int powerDigit = x % power; /* the digit in the base of power */
        
        printf("power digit: %d\n", powerDigit);
        /* && (powerDigit != 1 || x == power) */
		  
        if (powerDigit != 0) {
            
            /* isPower = 0;*/ 
            
            /* break; */
            
            return 0;
        
        }
    
        x = x / power;
    
    }
    
    /* return isPower; */
    return 1;
    
}

int main() {
    
    int n;
    
    printf("Enter n: ");
    
    scanf("%d", &n);
    
    printf("n = %d\n", n);
    
    /* printf("res = %d\n", isPowerOf(n, 5)); */
    
    if (isPowerOf(n, 5)) printf("%d is power of 5", n);
    else printf("%d is not power of 5", n);
    
    printf("\n");
  
    system("pause");
    
    return 0;
    
}
