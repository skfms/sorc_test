// g++ -o otl_odbc_mysql -I $TESTROOT/include otl_odbc_mysql.cpp -lodbc

#include <iostream>
using namespace std;

#include <stdio.h>

#define OTL_ODBC_UNIX
#define OTL_ODBC_MYSQL
#define OTL_ODBC_SELECT_STM_EXECUTE_BEFORE_DESCRIBE
#define OTL_STL
#include <otl/otlv4.h>

otl_connect db;

void insert()
{ 
	char buf[20];

	otl_stream o(1, "insert into test_tab values(:f1<int>,:f2<char[21]>)", db);
	for(int n=0; n<=100; n++)
	{
		sprintf(buf, "테스트 %d", n);
		o << n << buf;
	};
}

void select()
{ 
	otl_stream s(50, "select * from test_tab where f1 >= :f11<int> and f1 <= :f12<int>*2", db); 
	s << 8 << 8;
	
	int f1;
	string f2;
	
	while(!s.eof())
	{
		s >> f1 >> f2;
		cout << "f1:" << f1 << " f2:" << f2 << endl;
	};
}

int main()
{
	otl_connect::otl_initialize();

	try
	{
		db.rlogon("root/pwd@mariadb");

		otl_cursor::direct_exec(db, "drop table test_tab",otl_exception::disabled);
		otl_cursor::direct_exec(db, "create table test_tab(f1 int, f2 varchar(20))");

		insert();
		select();
		
		otl_cursor::direct_exec(db, "drop table test_tab");
	}
	catch(otl_exception& p)
	{
		cerr<<p.msg<<endl;
		cerr<<p.stm_text<<endl;
		cerr<<p.var_info<<endl;
	}

	db.logoff();

 return 0;
}
