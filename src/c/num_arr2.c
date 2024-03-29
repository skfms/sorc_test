// gcc -g -o num_arr2 num_arr2.c

#include <unistd.h>
#include <stdio.h>

void func(int v_arg[][5])
{ 
	v_arg[3][3] = 123;
}

int main()
{
	int aaa[10][5]; 

	aaa[3][3] = 999;

	printf(">>> %d\n", aaa[3][3]);
	func(aaa); 
	printf(">>> %d\n", aaa[3][3]);
	
};


