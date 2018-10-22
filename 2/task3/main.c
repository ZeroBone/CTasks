#include <stdio.h>
#include <stdlib.h>

int convertToNumber(int d1, int d2, int d3) {
    
    return d3 + (d2 * 10) + (d1 * 100);
        
}

int f(int number) {
    
    int digit1, digit2, digit3;
    
    int initialNumber = number;
    
    digit3 = number % 10;
    
    number /= 10;
    
    digit2 = number % 10;
    
    number /= 10;
    
    digit1 = number;/* % 10; */
    
    printf("Digits: %d %d %d\n", digit1, digit2, digit3);
    
    /* check whether all digits are different */
    if (digit1 != digit2 && digit2 != digit3 && digit1 != digit3) return initialNumber;
    
    if (digit1 == digit2 && digit1 == digit3) {
               
        /* all digits are the same */
        
        digit1--;
        
        if (digit3 != 9) digit3++;
        
        printf("Got digits: %d %d %d\n", digit1, digit2, digit3);
        
        return convertToNumber(digit1, digit2, digit3);
    
    }
    
    /* 2 digits are the same */
    /* swap digit1 and digit 3 */
	/* as a matter of fact, the values can be swapped without a temp variable */
    int temp = digit1;
    
    digit1 = digit3;
    
    digit3 = temp;
    
    return convertToNumber(digit1, digit2, digit3);
    
    /* we have already handled the case when
    all digits are the same, or all of them are different */
    /*if (digit1 == digit3 || digit2 == digit3 || digit1 == digit2) {
               
        
               
    }
    
    return -1;*/
    
}

int main() {
    
    int number;
    
    while (1) {
          
        printf("Enter number: ");
    
        scanf("%d", &number);
        
        if (number < 1e2 || number >= 1e3) printf("Invalid number entered, try again.\n");
        else break;
          
    }
    
    printf("Number received: %d\n\n", number);
    
    printf("Result: %d\n", f(number));
    
    
    system("pause");
    
    return 0;
}
