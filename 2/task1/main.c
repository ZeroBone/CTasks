#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double f(int t, int s) {
       
    if (t >= s && s > 2 && s <= 4) {
          
        return pow(t - s, 1 / 4);
          
    }
    
    if (t < 0) {
        
        return pow(s, 4) + (2 * t);
              
    }
    
    return t + 2;
       
}

int main() {
    
    int t, s;
    
    printf("t = ");
    
    scanf("%d", &t);
    
    printf("s = ");
    
    scanf("%d", &s);
    
    printf("Input: t = %d, s = %d\n", t, s);
    
    double result = f(t, s);
    
    printf("f = %lf\n", result);
  
    system("pause");
    	
    return 0;
    
}
