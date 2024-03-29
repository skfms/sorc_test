// gcc -g -o str_ptr3 str_ptr3.c

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int func(char *** v_arg);

int main()
{
	char **a = 0L;

	int count = func(&a);
	printf(">>> %s\n", a[3]);

	for(int n=0; n<count; n++) free(a[n]);
	free(a);
};

int func(char *** v_arg)
{
	int count = 5;

	char ** b = (char **)malloc(count * sizeof(char *));
	for(int n=0; n<count; n++) b[n] = (char *)malloc(100);
	strcpy(b[3], "Test !");
	*v_arg = b;

	return count;
}

