#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/*
k = 1024.000000
For x = 2, min power is 11, because 2 ^ 11 = 2048 > 1024, 2 ^ 10 = 1024 <= 1024
For x = 3, min power is 7, because 3 ^ 7 = 2187 > 1024, 3 ^ 6 = 729 <= 1024
For x = 4, min power is 6, because 4 ^ 6 = 4096 > 1024, 4 ^ 5 = 1024 <= 1024
For x = 5, min power is 5, because 5 ^ 5 = 3125 > 1024, 5 ^ 4 = 625 <= 1024
For x = 6, min power is 4, because 6 ^ 4 = 1296 > 1024, 6 ^ 3 = 216 <= 1024
For x = 7, min power is 4, because 7 ^ 4 = 2401 > 1024, 7 ^ 3 = 343 <= 1024
For x = 8, min power is 4, because 8 ^ 4 = 4096 > 1024, 8 ^ 3 = 512 <= 1024

=======================

k = 511.000000
For x = 2, min power is 9, because 2 ^ 9 = 512 > 511, 2 ^ 8 = 256 <= 511
For x = 3, min power is 6, because 3 ^ 6 = 729 > 511, 3 ^ 5 = 243 <= 511
For x = 4, min power is 5, because 4 ^ 5 = 1024 > 511, 4 ^ 4 = 256 <= 511
For x = 5, min power is 4, because 5 ^ 4 = 625 > 511, 5 ^ 3 = 125 <= 511
For x = 6, min power is 4, because 6 ^ 4 = 1296 > 511, 6 ^ 3 = 216 <= 511
For x = 7, min power is 4, because 7 ^ 4 = 2401 > 511, 7 ^ 3 = 343 <= 511
For x = 8, min power is 3, because 8 ^ 3 = 512 > 511, 8 ^ 2 = 64 <= 511


*/

int findMinPowerGreaterThan(int base, double threshold) {

    double value = 1;

    int power = 0;

    while (value <= threshold) {

        value *= base;

        power++;

    }

    return power;

}

/* the greater the enthropy, the more performance on long ranges  */
int z_findMinPowerGreaterThan(int base, double threshold, int startPower, int enthropy) {
	
	int power = startPower;

	short int toRight = 1;
	
	int iterations = 0; /* debug line */

	double powResult, previousPowResult;
	
	while (enthropy != 0) {
		
		if (toRight) {

			powResult = pow(base, power);
			
			while (powResult <= threshold) {
				
				iterations++;
				
				previousPowResult = powResult;
				
				powResult *= pow(base, enthropy);
				
				if (powResult < previousPowResult) {
					
					/* integer overflow */
					
					goto mark;
					
				}
				
				power += enthropy;
				
			}
			
		}
		else {
			
			/* int powResult = intPow(base, power - 1); */
            powResult = pow(base, power - 1);

			while (powResult > threshold) {
				
				powResult /= pow(base, enthropy);
				
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

    double k;
	
	printf("Enter k: ");
	
	scanf("%lf", &k);
	
	/*int enthropy;
	
	printf("Enter enthropy value (if you don't know what it is, enter \"4\"): ");
	
	scanf("%d", &enthropy); */
	
	/* validation casting */
	
	if (k < 0) k = 0;
	/* if (enthropy < 1) enthropy = 1; */
	
	printf("k = %lf\n", k);
	/* printf("enthropy = %d\n", enthropy); */

	int x = 2;
	
	for (; x <= 8; x++) {
		
		int minPower = findMinPowerGreaterThan(x, k);
		
		printf("For x = %d, min power is %d, because %d ^ %d = %.lf > %.lf, %d ^ %d = %.lf <= %.lf\n", x, minPower, x, minPower, pow(x, minPower), k, x, minPower - 1, pow(x, minPower - 1), k);
		
	}
	
	system("pause");
	
	return 0;
	
}
