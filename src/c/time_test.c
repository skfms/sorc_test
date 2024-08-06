// gcc -g -o time_test time_test.c

#include "unistd.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"

#include "time.h"

// **********************************************
int main(int v_argc, char *v_argv[])
{
	
	printf("start..\n");
	time_t begin = time(0L);

	sleep(3);

	time_t end = time(0L);

	printf("elapsed time : %lf sec\n", (double)(end - begin));
};

