// g++ -g -o str_ptr2 str_ptr2.c

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void func2(char * v_pbuf)
{
	sprintf(v_pbuf, "test !");
};

void func1()
{
	char pbuf[100];

	func2(pbuf);
	fprintf(stdout, "%s\n", pbuf);
};


int main()
{
	func1();
};
