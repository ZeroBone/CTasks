#include <stdio.h>
#include <stdlib.h>

int main() {
	
	printf("ZeroBone\n");
	
	int arr[] = {1, 2, 3, 4, 5};
	int b[] = {1, 2, 3, 4, 5, 6}, c[5], d[] = {2, 4, 6, 8, 10};
	
	/* c = arr; */
	scanf("%d", c);
	printf("b > arr: %d\n", b > arr);
	printf("b == arr: %d\n", b == arr);
	printf("d < arr: %d\n", d < arr);
	
	system("pause");
	
	return 0;
	
}
