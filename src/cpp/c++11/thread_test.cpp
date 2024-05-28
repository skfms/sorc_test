// g++ -o thread_test thread_test.cpp

#include "unistd.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"

#include "strings.h"

#include <vector>
#include <map>

#include <iostream>
#include <string>
#include <thread>
#include <atomic>
#include <chrono>

using namespace std;
void usage(char * v_command);

void test_01();
void test_02();
void test_03();
void test_04();
void test_05();
void test_06();


// **********************************************
atomic<bool> stop_flag (false);
atomic<bool> end_flag (false);

class myclass {
	public:
		void f1(int x) {
			for(int n=0; n<x; n++) cout << "class : " << n << endl;
		};
};

void func(const string &msg, int num) { cout << msg << " : " << num << endl; };

void func_wait() 
{ 
	while(1) {
		this_thread::sleep_for(chrono::milliseconds(500));
		cout << "thread run ...." << endl;
		if(stop_flag.load()) break;
	};
	end_flag.store(true);
};

void func_2s() 
{
	this_thread::sleep_for(chrono::seconds(2));
};

map<int, void (*)(void)> funcmap =
{
  { 1, &test_01 },
  { 2, &test_02 },
  { 3, &test_03 },
  { 4, &test_04 },
  { 5, &test_05 },
  { 6, &test_06 }
};

// **********************************************
int main(int v_agrc, char * v_argv[])
{
	char *pcmd = v_argv[0];
	if(v_agrc < 2) usage(pcmd);
	
	int index = atoi(v_argv[1]);
	if(index > funcmap.size()) usage(pcmd);
	
	funcmap[index]();
}


// **********************************************
void usage(char * v_command)
{
	char *pt = rindex(v_command, '/');
	pt = (pt == 0L ? v_command : ++pt);
	
	printf(
		"Usage: %s [index]\n"
		"  index   1 run a lambda function\n"
		"          2 run a class function\n"
		"          3 passing argument\n"
		"          4 declaring and executing objects\n"
		"          5 detach thread process\n"
		"          6 get thread id\n\n"
		, pt
		);
	exit(0);
}

// **********************************************
// lambda 함수
void test_01()
{
	thread t([] {
		for(int n=0; n<5; n++) cout << "thread t : " << n << endl;
	});
	
	for(int n=0; n<5; n++) cout << "main : " << n << endl;
	
	t.join();
}

// **********************************************
// class 호출
void test_02()
{
	myclass obj;
	
	thread t(&myclass::f1, &obj, 5);
	
	t.join();
}


// **********************************************
// 인자 전달
void test_03()
{
	string a = "Hello World !";
	int n = 123;
	
	thread t(func, a, n);
	
	t.join();
}


// **********************************************
// 객체 선언 후 실행
void test_04()
{
	string a = "Hello World !";
	int n = 123;
	
	thread t;
	
	t = thread(func, a, n);
	
	t.join();
}


// **********************************************
// 분리된 Thread 종료
void test_05()
{
	thread t(func_wait);
	t.detach();
	
	this_thread::sleep_for(chrono::seconds(2));
	stop_flag.store(true);
	
	while(!end_flag.load());
	
	cout << "end complete !" << endl;
}


// **********************************************
// Thread ID
void test_06()
{
	thread::id id_main = this_thread::get_id();
	cout << "main thread id = " << id_main << endl;
	
	thread t(func_2s);
	thread::id id_child = t.get_id();
	cout << "child thread id = " << id_child << endl;
	
	t.join();
}