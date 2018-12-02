#include <stdio.h>
#include <stdlib.h>

typedef void (*voidF)(int);
typedef voidF (*recF)(int);

voidF recurrentFunction(int n) {
	
    printf("F: %d\n", n);
    
    return (voidF)recurrentFunction;
    
}

int main() {
	
	/*recF f = (recF)recurrentFunction;
	
	f = (recF)f(2);
	f = (recF)f(3);
	f = (recF)f(4);
	f = (recF)f(5);
	
	f = (recF)f(100);
	
	f(6);*/


	recF f = recurrentFunction;
	
	f = f(1);
	f = f(2);
	f = f(3);
	f = f(4);
	f = f(5);
	
	f = f(100);
	
	f(6);
	
	
	system("pause");
	
	return 0;
	
}
