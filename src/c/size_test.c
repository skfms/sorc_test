// g++ -g -o size_test size_test.c
// g++ -g -m32 -o size_test size_test.c

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string>

int main()
{
	
	printf("off_t size = %ld\n", sizeof(off_t));

};
