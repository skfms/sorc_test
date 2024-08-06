// gcc -g -o notation notation.c

#include "unistd.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"

void usage(char * v_cmd);
char * notation(long long v_value, int v_convnum, char *v_pt);

#define MAX_SZ	50

// **********************************************
int main(int v_argc, char *v_argv[])
{
	if(v_argc < 3) usage(v_argv[0]);
	
	char buf[MAX_SZ];
	buf[MAX_SZ-1] = 0x00;
	char *pt = & buf[MAX_SZ-2];
	
	int convnum = atoi(v_argv[1]);
	long long value = atoll(v_argv[2]);
	
	pt = notation(value, convnum, pt);
	printf(
		"input : %lld\n"
		"conv  : %s\n",
		value, pt
		);
};

// **********************************************
void usage(char * v_cmd)
{
	char *pcmd = rindex(v_cmd, '/');
	pcmd = (pcmd == 0L ? v_cmd : ++pcmd);

	printf(
		"Usage: %s <conv_notation> <value>\n"
		, pcmd
		);
	exit(0);
}

// **********************************************
char * notation(long long v_value, int v_convnum, char *v_pt)
{
	if(v_value == 0) return v_pt+1;

	char *pt = notation(v_value / v_convnum, v_convnum, v_pt-1);
	int val = v_value % v_convnum;
	*v_pt = val + (val < 10 ? '0' : (-10)+'A');

	return pt;
};
