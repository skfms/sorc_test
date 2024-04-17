// g++ -g -o str_replace str_replace.cpp ./../../comm_cpp/sutil.cpp ./../../comm_cpp/exception.cpp

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <iostream>

#include "./../../comm_cpp/sutil.h"

int main()
{
	const char *ptext = "SELECT now(), NOW() From Now( )";

	string t1 = csutil::str_replace(ptext, "now()", "sysdate");
	string t2 = csutil::str_replace(ptext, "now()", "sysdate", 1);
	
	printf(
		"org [%s]\n"
		"cvt #1 [%s]\n"
		"cvt #2 [%s]\n",
		ptext, t1.c_str(), t2.c_str());
};
