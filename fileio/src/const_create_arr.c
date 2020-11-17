#include <stdio.h>

int func()
{
	int a = 3, b = 4;
	int c = a * b;
	return c;
}

int main()
{
	const int N = 10;
	int arr[N];
	printf("size = %ld\n", sizeof(arr));

	int x = 10;
	const int SIZE = x;
	int buf[SIZE];
	printf("size = %ld\n", sizeof(buf));
	
	const int FN = func();
	int buf2[FN];
	printf("size = %ld\n", sizeof(buf2));

	return 0;
}
