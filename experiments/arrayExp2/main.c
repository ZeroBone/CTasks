#include <stdio.h>
#include <stdlib.h>

int main() {
	
	int ar[3][3] = {1, 2, 3,
					4, 5, 6,
					7, 8, 9};
					
	int **p;
	
	/*int i,j, **p;
	
	for (i = 0; i < 2; i++) {
		
		for (j = 6; j > 2; j--) {
			
			printf("%d", ar[i][j]);
			
		}
		
		printf("\n");
		
	}*/
	
	p = ar;
	p[1][0] = 10;
	
	printf("===============\n");
	int i;
	for (i = 0; i < 9; i++) {
		
		printf("%d\n", p[i]);
		
	}
	
	/*int x, y;
	
	for (y = 0; y < 3; y++) {
		
		for (x = 0; x < 3; x++) {
			
			printf("%d ", ar[y][x]);
			
		}
		
		printf("\n");
		
	}*/
	
	system("pause");
	
	return 0;
	
}
