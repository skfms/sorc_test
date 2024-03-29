// gcc -g -o num_arr1 num_arr1.c

#include <unistd.h>
#include <stdio.h>

void func(int * v_arg);

int main()
{
	int a[3];

	a[1] = 99;
	printf(">>> %d\n", a[1]);
	func(a);
	printf(">>> %d\n", a[1]);
	
};

void func(int * v_arg)
{
	v_arg[1] = 88;
}
