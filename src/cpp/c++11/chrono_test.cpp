// g++ -o chrono_test chrono_test.cpp

#include "unistd.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"

#include "strings.h"

#include <iostream>
#include <chrono>
#include <thread>

using namespace std;

void test_01();

// **********************************************
int main()
{
	test_01();
}

// **********************************************
void test_01()
{
	auto start = std::chrono::high_resolution_clock::now();
	
	this_thread::sleep_for(std::chrono::seconds(1));
	
	auto stop = std::chrono::high_resolution_clock::now();
	
	auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);

    std::cout << "Time taken by function: " << duration.count() << " microseconds" << std::endl;
}

