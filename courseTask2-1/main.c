#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/*
t = 4, s = 4, res = 0
t = 10, s = 4, res = 1.565085
t = 3, s = 4, res = 5
*/

double f(int t, int s) {
	
	return (t >= s && s > 2 && s <= 4) ? pow(t - s, 1.0 / 4) : (
		t < 0 ? pow(s, 4) + (2 * t) : t + 2
	);

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
