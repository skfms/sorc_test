// gcc -g -o han_cut han_cut.c

#include "unistd.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"

void usage(char * v_cmd);
char * han_cut(char * v_data, int v_cutlen);

// **********************************************
int main(int v_argc, char *v_argv[])
{
	if(v_argc < 3) usage(v_argv[0]);
	
	int cutlen = atoi(v_argv[1]);
	
	char * out = han_cut(v_argv[2], cutlen);
	
	printf(
		"cut: %d\n"
		"in : [%s]\n"
		"out: [%s]\n",
		cutlen, v_argv[2], out
		);
};


// **********************************************
void usage(char * v_cmd)
{
	printf(
		"Usage: %s <cut_length> <string>\n"
		, v_cmd
		);
	exit(0);
}



// **********************************************
char * han_cut(
	char * v_data,
	int v_cutlen
)
{
	static char retdata[101];

	if (v_cutlen <= 0) return v_data;
	if (strlen(v_data) <= v_cutlen) return v_data;

	printf(">>> %ld\n", strlen(v_data));

	memset(retdata, 0x00, sizeof(retdata));
	
	int acclen = 0;
	unsigned char *pt = &retdata[0];
	unsigned char *ps = &v_data [0];
	
	while(*ps)
	{
		if (*ps < 0x7F)
		{
			*pt++ = *ps++;
			acclen++;
		}
		else
		{
			*pt++ = *ps++;
			*pt++ = *ps++;
			acclen += 2;
		};
		
		printf("%d [%s]\n", acclen, retdata);

		if (acclen + 2 >= v_cutlen)
		{
			*pt++ = '.';
			*pt++ = '.';
			break;
		};
	};
	
	return retdata;
};

