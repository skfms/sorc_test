// g++ -o pqxx_test -I/home/leegs/com_vender/libpqxx/include -L/home/leegs/com_vender/libpqxx/lib -l pqxx pqxx_test.cpp

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <iostream>
#include <pqxx/pqxx>

using namespace std;

pqxx::connection * g_pconn = 0L;

//###########################
void db_connect()
{
	g_pconn = new pqxx::connection(
		"user=xxxx "
		"password=xxxxx "
		"hostaddr=xxx.xxx.xxx.xxx "
		"port=5432 "
		"dbname=xxxxx"
		);
  
	if (g_pconn->is_open()) 
		fprintf(stdout, "Opened database [%s] successfully\n", g_pconn->dbname());
	else 
		fprintf(stderr, "Can't open database\n");
};

//###########################
void db_disconnect()
{
	if(g_pconn) g_pconn->disconnect();
	g_pconn = 0L;
};

//###########################
void test_01()
{
	pqxx::result rst;
	
	pqxx::work w(*g_pconn);
	
	w.exec("drop table if exists test_01");
	
	w.exec("create table test_01(id integer, name varchar(50), tel varchar(30))");
	fprintf(stdout, "create table [test_01]\n");
	
	rst = w.exec("insert into test_01 values(1, '홍길동', '010-9999-5319'), (2, '김유신', '010-8888-1562')");
	fprintf(stdout, "insert count = %d\n", rst.affected_rows());
	
	string t_line;
	
	rst = w.exec("select * from test_01");
	for(auto row : rst)
	{
		t_line = "";
		for(auto col : row)
		{
			if(!t_line.empty()) t_line += ", ";
			t_line += col.c_str();
		}
		
		fprintf(stdout, "%s\n", t_line.c_str());
	};
	
	w.exec("drop table if exists test_01");
	
	w.commit();
};

//###########################
void test_02()
{
	pqxx::result rst;
	
	pqxx::work w(*g_pconn);
	
	w.exec("drop table if exists test_02");
	
	w.exec("create table test_02(id integer, name varchar(50), tel varchar(30))");
	fprintf(stdout, "create table [test_01]\n");
	
	g_pconn->prepare("test_02", "insert into test_02 values($1, $2, $3)");
	
	for(int n=1; n<10000; n++)
		rst = w.exec_prepared("test_02", n, "홍길동", "010-XXXX-9999");
	fprintf(stdout, "insert data\n");
	
	rst = w.exec("select * from test_02");

	for(auto row : rst)
	{
		fprintf(stdout, "%d, %s\n", row["id"].as<int>(), row["name"].c_str());
		break;
	};
	
	w.exec("drop table if exists test_02");
	
	w.commit();
};


//###########################
int main(int, char **)
{
	try
	{
		db_connect();
		
		test_01();
		//test_02();
		
		db_disconnect();
	}
	catch (pqxx::sql_error e)
	{
		fprintf(stderr, "query : [%s]\nerror : %s\n", e.query(), e.what());
	}
	catch (exception e)
	{
		fprintf(stderr, "error : %s\n", e.what());
	};
};