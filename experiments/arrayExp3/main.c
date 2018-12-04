#include <stdio.h>
#include <stdlib.h>
#define N 5

int main() {
	
	int ar[N][N];
	int i, j;
	int sum = 0;
	
	for (i = 0; i < N; i++) {
		
		for (j = 0; j < N; j++) {
			
			scanf("%d", &ar[i][j]);
			
		}
		
	}
	
	for (i = 0; i < N / 2; i++) {
		
		for (j = 0; j <= i; j++) {
			
			sum += ar[i][j];
			sum += ar[N - i - 1][N - j - 1];
			
		}
		
	}
	
	printf("Sum = %d\n", sum);
	
	system("pause");
	
	return 0;
	
}
