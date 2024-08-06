// g++ -g -o time_test time_test.cpp
#include "unistd.h"

#include <iostream>
#include <chrono>

using namespace std;
using namespace chrono;


// **********************************************
int main(int v_argc, char *v_argv[])
{
	system_clock::time_point begin = system_clock::now();

	sleep(3);

	system_clock::time_point end = system_clock::now();

	nanoseconds nsec = end - begin;
	microseconds misec = duration_cast<microseconds>(end - begin);
	milliseconds mlsec = duration_cast<milliseconds>(end - begin);
	seconds sec = duration_cast<seconds>(end - begin);
	minutes min = duration_cast<minutes>(end - begin);
	hours hour = duration_cast<hours>(end - begin);

	cout << " nano time : " << nsec.count() << endl;
	cout << "micro time : " << misec.count() << endl;
	cout << "milli time : " << mlsec.count() << endl;
	cout << "  sec time : " << sec.count() << endl;
	cout << "  min time : " << min.count() << endl;
	cout << " hour time : " << hour.count() << endl;
};

