#include <stdio.h>

#define IS_INTPTR(x) _Generic ((x), int*: 1, default: 0)

int main()
{
	
	int arr[5] = {1, 2, 3, 4, 5};
	int* aptr = arr;
	int a = 1;
	
	printf("%d %d %d\n", IS_INTPTR(aptr), IS_INTPTR(arr), IS_INTPTR(a));
	
	return 0;
}