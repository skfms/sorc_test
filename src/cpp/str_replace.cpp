// g++ -g -o str_replace str_replace.cpp ./../../comm_cpp/sutil.cpp ./../../comm_cpp/exception.cpp

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <iostream>

#include "./../../comm_cpp/sutil.h"

int main()
{
	const char *ptext = 
		"INSERT INTO STAT_LOAD_T(        start_dt, stat_ind, machine, machine_id, end_dt, crt_dt,        musr, msys,"
		"midle, avusr, avsys, avidle, status_ind) VALUES(       '202404191200', '10', 10, 1, '202404191210', now(),       0, 0, 0, 0, 0,"
		"0, 'N')";

	string t1 = csutil::str_replace(ptext, "now()", "sysdate");
	string t2 = csutil::str_replace(ptext, "now()", "sysdate", 1);
	
	printf(
		"org [%s]\n"
		"cvt #1 [%s]\n"
		"cvt #2 [%s]\n",
		ptext, t1.c_str(), t2.c_str());
};
