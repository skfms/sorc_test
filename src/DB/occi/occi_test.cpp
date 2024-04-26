// g++ -g -o occi_test -D_GLIBCXX_USE_CXX11_ABI=0 -I $TESTROOT/include/oracle occi_test.cpp -L $ORACLE_HOME/lib -locci -lclntsh
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

int main()
{

	try 
	{
		connect();
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
	g_penv = Environment::createEnvironment(Environment::DEFAULT);
	g_pconn = g_penv->createConnection("leegs", "ahffk", "(DESCRIPTION=(ADDRESS=(PROTOCOL=TCP)(HOST=172.21.20.26)(PORT=1521))(CONNECT_DATA=(SERVICE_NAME=orcl)))");
	cerr << "Oracle Connected Ok !" << endl;
};

void close()
{
	if (g_pconn) g_penv->terminateConnection(g_pconn);
	if (g_penv ) Environment::terminateEnvironment(g_penv);
};