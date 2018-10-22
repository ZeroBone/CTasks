#include <stdio.h>
#include <stdlib.h>
#include <math.h>

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
