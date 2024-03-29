// gcc -g -o struct_arr1 struct_arr1.c

#include <unistd.h>
#include <stdio.h>

struct AAA {
	int n1;
	char n2[10];
};

void func(struct AAA p[][5]) 
{ 
	p[9][3].n1 = 123; 
}

int main()
{
	struct AAA aaa[10][5];

	aaa[9][3].n1 = 999;

	printf(">>> %d\n", aaa[9][3].n1);
	func(aaa); 
	printf(">>> %d\n", aaa[9][3].n1);
};


