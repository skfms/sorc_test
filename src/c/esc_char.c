// gcc -g -o esc_char esc_char.c

#include "unistd.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"

void usage(char * v_cmd);
void escape(char * v_data);

#define BLUE "\e[34m"
#define RED "\e[31m"
#define DEF "\e[0m"

// **********************************************
int main(int v_argc, char *v_argv[])
{
	if(v_argc < 2) usage(v_argv[0]);
	
	escape(v_argv[1]);
};

// **********************************************
void usage(char * v_cmd)
{
	printf(
		"Usage: %s <string>\n"
		, v_cmd
		);
	exit(0);
}

// **********************************************
void escape(char *v_data)
{
	char *pt = strcasestr(v_data, "ABRT");
	
	if(pt)	printf("%s%s%s\n", RED, v_data, DEF);
	else	printf("%s\n", v_data);
};