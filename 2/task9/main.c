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

	int toRight = 1;
	
	int iterations = 0; /* debug line */
	
	while (enthropy != 0) {
		
		if (toRight) {
			
			/* TODO try using do while cause */
			while (intPow(base, power) <= threshold) {
			
				/* leftBorder = power; */
				
				power += enthropy;
				
				iterations++; /* debug line */
				
			}
			
			/* if (z_powerOk(base, power, threshold)) {*/
				
				/* we've found the right power */
				/* break 2; in php, break topMark; in js, java and ts */
				/* goto topMark; */
				
			/*}*/
			
			toRight = 0;
			
		}
		else {
			
			while (intPow(base, power - 1) > threshold) {
				
				power -= enthropy;
				
				iterations++; /* debug line */
				
			}
			
			/* if (z_powerOk(base, power, threshold)) {*/
				
				/* we've found the right power */
				/* break 2; in php, break topMark; in js, java and ts */
				/* goto topMark; */
				
			/*}*/
			
			toRight = 1;
			
		}
		
		enthropy /= 2;
		
	}
	
	topMark:
		
	printf("=======================\nIterations: %d\n=======================\n", iterations);
	
	return power;
	
}

int main(int argc, char *argv[]) {
	
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
		
		printf("For x = %d, minimum power is %d, because %d ^ %d = %d > %d, %d ^ %d = %d <= %d\n\n", x, minPower, x, minPower, intPow(x, minPower), k, x, minPower - 1, intPow(x, minPower - 1), k);
		
	}
	
	system("pause");
	
	return 0;
	
}
