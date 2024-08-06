// g++ -o semaphore_test semaphore_test.cpp

#include "unistd.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"

#include "strings.h"

#include <fcntl.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <semaphore.h>

#include <vector>
#include <map>

#include <iostream>
#include <string>
#include <thread>
#include <chrono>

using namespace std;

#define sem_id "sem"
sem_t g_sem;

void usage(char * v_command);

void test_01();
void test_02();

map<int, void (*)(void)> funcmap =
{
  { 1, &test_01 },
  { 2, &test_02 },
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
		"  index   1 thread test\n"
		"          2 process test\n"
		, pt
		);
	exit(0);
}

// **********************************************
// lambda 함수
void test_01()
{
	int num = 5;

	int state = sem_init(&g_sem, 0, 3);
	if(state != 0)
	{
		perror("sem_init()");
		exit(-1);
	};

	vector<thread> works;
	for(int n=0; n<num; n++)
	{
		sem_wait(&g_sem);

		works.push_back(thread([]()
		{
			printf("thread id = %ld\n", this_thread::get_id());
			sleep(2);
			sem_post(&g_sem);
		}));
	};
	
	for(auto & t : works) 
    {
        t.join();
    };
	
	sem_destroy(&g_sem);
}

// **********************************************
// class 호출
void test_02()
{
	int num = 10;
	
	sem_t *sem = sem_open(sem_id, O_CREAT | O_EXCL, 0644, 3);
	if(sem == SEM_FAILED)
	{
		perror("sen_open()");
		exit(-1);
	};
	
	for(int n=0; n<num; n++)
	{
		sem_wait(sem);

		if(fork() == 0)
		{
			printf("child pid = %d\n", getpid());
			sleep(2);
			sem_post(sem);
			exit(0);
		};
	};
	
	for(int n=0; n<num; n++) wait(0L);
	
	sem_close(sem);
	sem_unlink(sem_id);
	
	printf("end process !\n");
}


