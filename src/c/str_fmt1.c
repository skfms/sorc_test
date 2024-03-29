// g++ -g -o str_fmt1 str_fmt1.c

#include <unistd.h>
#include <stdio.h>

#include <string>

int main()
{
	
	printf("1 : [%20s]\n", "Test");
	printf("2 : [%*s]\n", 20, "Test");

	printf("3 : [%-*s]\n", 20, "Test");
	printf("4 : [%-20s %s]\n", "Test aaaaaaaaaaaaaaaaaaa bbbbbbbbb", "bbb");

	printf("5 : [%s]\n", std::string(20, '=').c_str());
};
