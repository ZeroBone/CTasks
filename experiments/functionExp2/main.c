#include <stdio.h>
#include <stdlib.h>

typedef void* (*FPointer)(int);

void* f(int);

int main() {
	
	/*FPointer f1 = f(1);
    FPointer f2 = f1(2);
    FPointer f3 = f2(3);*/
    
    FPointer result = f;
    
    result = result(1);
    result = result(2);
    result = result(3);
	
	system("pause");
	
	return 0;
	
}

void* f(int n) {
	
	printf("F: %d\n", n);
	
	return f;
	
}
