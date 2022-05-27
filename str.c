// g++ -g -o str str.c

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void func(char **v_buff)
{
	*v_buff = (char *)malloc(100);
	sprintf(*v_buff, "test !");
};

int main()
{
	char *t_buff;

	func(&t_buff);

	fprintf(stdout, "[%s]\n", t_buff);
};
