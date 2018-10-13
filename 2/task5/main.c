#include <stdio.h>
#include <stdlib.h>

int isPowerOf(int x, int power) {
    
    if (x == 1) return 1;
    
    if (x < power) return 0;
    
    int isPower = 1;
    
    while (x > 0) {
        
        int powerDigit = x % power; /* the digit in the base of power */
        
        /* printf("power digit: %d\n", powerDigit); */
          
        if (powerDigit != 0 && (powerDigit != 1 || x == power)) {
            
            isPower = 0;
            
            break;
        
        }
    
        x = x / power;
    
    }
    
    return isPower;
    
}

int main() {
    
    int n;
    
    printf("Enter n: ");
    
    scanf("%d", &n);
    
    printf("n = %d\n", n);
    
    if (isPowerOf(n, 5)) printf("%d is power of 5", n);
    else printf("%d is not power of 5", n);
    
    printf("\n");
  
    system("pause");
    
    return 0;
    
}
