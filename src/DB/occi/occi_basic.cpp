// g++ -g -o occi_basic -D_GLIBCXX_USE_CXX11_ABI=0 -I $TESTROOT/include/oracle occi_basic.cpp -L $ORACLE_HOME/lib -locci -lclntsh
// ubuntu : 
//  -D_GLIBCXX_USE_CXX11_ABI=0 옵션 필요, 
//  - ORA-24960: the attribute  OCI_ATTR_USERNAME is greater than the maximum allowable length of 255        

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <iostream>

#include "occi.h"

using namespace oracle::occi;
using namespace std;

Environment *	g_penv = 0L;
Connection *	g_pconn = 0L;

void connect();
void close();
void create();
void insert();
void select();
void drop();

int main()
{

	try 
	{
		connect();
		create();
		insert();
		select();
		drop();
		close();
	}
	catch(SQLException & ex) 
	{
		//if (pResultSet) pStatement->closeResultSet(pResultSet);
		//if (pStatement) pConnection->terminateStatement(pStatement);
		cerr << "Error number:" << ex.getErrorCode() << ":" << ex.getMessage() << endl;
	}
	catch(...)
	{
		cerr << "UnknowException" << endl;
	}
}

void connect()
{
	g_penv = Environment::createEnvironment("UTF8", "KO16MSWIN949", Environment::DEFAULT);
	g_pconn = g_penv->createConnection("leegs", "ahffk", "(DESCRIPTION=(ADDRESS=(PROTOCOL=TCP)(HOST=172.21.20.26)(PORT=1521))(CONNECT_DATA=(SERVICE_NAME=orcl)))");
	cerr << "Oracle Connected Ok !" << endl;
};

void close()
{
	if (g_pconn) g_penv->terminateConnection(g_pconn);
	if (g_penv ) Environment::terminateEnvironment(g_penv);
};

void create()
{
	string q = "CREATE TABLE TEST_001(id number not null, name varchar(50) not null, birth date)";

	Statement *pstmt = g_pconn->createStatement(q);
	pstmt->execute();
	
	printf(">>> create table : TEST_001\n");
	
	g_pconn->terminateStatement(pstmt);
};

void drop()
{
	string q = "DROP TABLE TEST_001 PURGE";

	Statement *pstmt = g_pconn->createStatement(q);
	pstmt->execute();
	
	printf(">>> drop table : TEST_001\n");
	
	g_pconn->terminateStatement(pstmt);
};

void insert()
{
	int bufsz =10;
	string q = "INSERT INTO TEST_001(id, name, birth) VALUES(:V1, :V2, :V3)";

	int id, rowcnt = 0, loop = 0, loopcnt = 35;
	string name = "이기선";
	Date date;
	date.fromText("20240426", "YYYYMMDD", "", g_penv);

	Statement *pstmt = g_pconn->createStatement(q);
	pstmt->setMaxIterations(bufsz+1);
	
	// 문자열 데이터일 경우 최대크기 설정
	pstmt->setMaxParamSize(2, 100);

	for(int n=0; n< loopcnt; n++)
	{
		pstmt->setInt(1, n+1);
		pstmt->setString(2, name);
		pstmt->setDate(3, date.addDays(n));

		if((n+1) % bufsz == 0)
		{
			pstmt->executeUpdate();
			loop = 0;
		}
		else if(n != loopcnt-1)
		{
			// 마지막 데이터일 경우 add 하지 않음
			pstmt->addIteration();
			loop++;
		};
		
		rowcnt++;
	};
	
	if(loop) pstmt->executeUpdate();

	g_pconn->commit();
	printf(">>> insert table [TEST_001] = %d\n", rowcnt);

	g_pconn->terminateStatement(pstmt);
};

void select()
{
	string q = "SELECT * FROM TEST_001";
	
	Statement *pstmt = g_pconn->createStatement(q);
	
	pstmt->setPrefetchRowCount(10);
	//pstmt->setPrefetchMemorySize(1024*64);
	
	ResultSet *pres = pstmt->executeQuery();
	
	auto colmd = pres->getColumnListMetaData();
	
	while(pres->next())
	{
		for(int n=0; n<colmd.size(); n++)
		{
			switch(colmd[n].getInt(MetaData::ATTR_DATA_TYPE))
			{
				case OCCI_SQLT_DAT:
					printf("d %s", pres->getDate(n+1).toText("YYYY-MM-DD HH24:MI:SS").c_str());
					break;
					
				case OCCI_SQLT_TIMESTAMP:
					printf("t %s", pres->getDate(n+1).toText("YYYY-MM-DD HH24:MI:SS.FF").c_str());
					break;

				case OCCI_SQLT_CLOB:
				case OCCI_SQLT_BLOB:
				case OCCI_SQLT_LNG :
					break;

				case OCCI_SQLT_CHR:
				case OCCI_SQLT_NUM:
				case OCCI_SQLT_STR:
				case OCCI_SQLT_VCS:
				default:
					printf("c %s", pres->getString(n+1).c_str());
			};
			printf("\t");
		};
		
		printf("\n");
	};
	
	pstmt->closeResultSet(pres);
	g_pconn->terminateStatement(pstmt);
};


