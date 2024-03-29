// g++ -g -o str_fmt1 str_fmt1.c

#include <unistd.h>
#include <stdio.h>

int main()
{
	
	printf("[%*s]\n", 20, "Test");
	printf("[%-*s]\n", 20, "Test");
	printf("[%-20s %s]\n", "Test aaaaaaaaaaaaaaaaaaa bbbbbbbbb", "bbb");
};
