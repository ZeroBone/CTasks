#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int intPow(int base, int power) {
	
	return (int)pow((int)base, (int)power);
	
}

int z_powerOk(int base, int power, int threshold) {
	
	return (intPow(base, power) > threshold && intPow(base, power - 1) <= threshold);
	
}

/* the greater the enthropy, the more performance on long ranges  */
int z_findMinPowerGreaterThan(int base, int threshold, int startPower, int enthropy) {
	
	int power = startPower;
	
/*	int leftBorder; */
/*	int rightBorder; */

	short int toRight = 1;
	
	int iterations = 0; /* debug line */
	
	while (enthropy != 0) {
		
		if (toRight) {
			
			int powResult = intPow(base, power);
			
			int previousPowResult;
			
			while (powResult <= threshold) {
				
				iterations++;
				
				previousPowResult = powResult;
				
				powResult *= intPow(base, enthropy);
				
				if (powResult < previousPowResult) {
					
					/* integer overflow */
					
					goto mark;
					
				}
				
				power += enthropy;
				
			}
			
		}
		else {
			
			int powResult = intPow(base, power - 1);
			
			while (powResult > threshold) {
				
				powResult /= intPow(base, enthropy);
				
				power -= enthropy;
				
				iterations++;
				
			}
			
			
		}
		
		toRight = !toRight;
		
		enthropy /= 2;
		
	}
	
	mark:
		
	printf("=======================\nIterations: %d\n", iterations);
	
	return power;
	
}

int main() {
	
	int k;
	
	printf("Enter k: ");
	
	scanf("%d", &k);
	
	int enthropy;
	
	printf("Enter enthropy value (if you don't know what it is, enter \"4\"): ");
	
	scanf("%d", &enthropy);
	
	/* validation casting */
	
	if (k < 0) k = 0;
	if (enthropy < 1) enthropy = 1;
	
	printf("k = %d\n", k);
	printf("enthropy = %d\n", enthropy);

	int x = 2;
	
	for (; x <= 8; x++) {
		
		int minPower = z_findMinPowerGreaterThan(x, k, 0, enthropy);
		
		printf("For x = %d, min power is %d, because %d ^ %d = %d > %d, %d ^ %d = %d <= %d\n", x, minPower, x, minPower, intPow(x, minPower), k, x, minPower - 1, intPow(x, minPower - 1), k);
		
	}
	
	system("pause");
	
	return 0;
	
}
