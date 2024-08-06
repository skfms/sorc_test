// gcc -g -o shift shift.c

#include <unistd.h>
#include <stdio.h>

void func(int * v_arg);

int main()
{
	int n = 99;
	printf(">>> %d, %d\n", n * 16384, n << 1 << 1 << 1 << 1 << 1 << 1 << 1 << 1 << 1 << 1 << 1 << 1 << 1 << 1);
	printf(">>> %d, %d\n", n * 16384, n << 14);
	
};

