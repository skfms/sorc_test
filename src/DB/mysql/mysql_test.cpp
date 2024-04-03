// g++ -g -std=gnu++11 -o mysql_test mysql_test.cpp -I ~/com_vender/MariaDB/include -L ~/com_vender/MariaDB/lib -l mariadbclient -L ~/com_vender/openssl/lib -lcrypto -lssl -ldl -lpthread -lz

#ifndef MYSQL_TEST_CPP
#define MYSQL_TEST_CPP

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <errno.h>

#include <string>

#include <mysql.h>

using namespace std;

//================================================
class cmysql
{
public:
	 cmysql();
	~cmysql();

public:
	void	init (
			const char *v_host	,
			int			v_port	,
			const char *v_uid	,
			const char *v_pwd	,
			const char *v_db		);
	int		connect();
	int		query (string v_query	);
	int		insert();
	char *	get_coltype(int v_type	);
	
private:
	MYSQL	*m_pdb;
	
	string	m_host;
	string	m_uid;
	string	m_pwd;
	string	m_db;
	int		m_port;
	
	void	init ();
	void	close();
};

//================================================


//+++++++++++++++++++++++++++++++++++++++++++++++++
int main()
{ 
	
	cmysql my;
	int r;
	
	my.init(0L, 0, "root", "rootpwd", "dac");
	r = my.connect();
	if(r != 0) exit(1);
	
	my.insert();
	my.query("select * from dac.CODE");
	
}


//+++++++++++++++++++++++++++++++++++++++++++++++++
cmysql::cmysql()
{
	init();
}


//+++++++++++++++++++++++++++++++++++++++++++++++++
cmysql::~cmysql()
{
	close();
}


//+++++++++++++++++++++++++++++++++++++++++++++++++
void cmysql::init()
{
	m_pdb = mysql_init(0L);
}


//+++++++++++++++++++++++++++++++++++++++++++++++++
void cmysql::init(
	const char *v_host,		// [IN ]
	int			v_port,		// [IN ]
	const char *v_uid,		// [IN ]
	const char *v_pwd,		// [IN ]
	const char *v_db = 0L	// [IN ]
)
{
	m_host	= v_host	? v_host: "";
	m_port	= v_port>0	? v_port: 0 ;
	m_uid	= v_uid		? v_uid : "";
	m_pwd	= v_pwd		? v_pwd : "";
	m_db	= v_db		? v_db	: "";
}


//+++++++++++++++++++++++++++++++++++++++++++++++++
void cmysql::close()
{
	if(m_pdb) mysql_close(m_pdb);
	m_pdb = 0L;
}


//+++++++++++++++++++++++++++++++++++++++++++++++++
int cmysql::connect()
{
	if(m_pdb == 0L) return -1;
	
	fprintf(stdout, ">>> host [%s] port [%d] uid [%s] pwd [%s] db [%s]\n", 
			m_host.c_str()	, 
			m_port			,
			m_uid.c_str()	,
			m_pwd.c_str()	,
			m_db.c_str()
			);
	
	//mysql_real_connect(&mysql, host, user, passwd, db, port, unix_socket, client_flag);
	if(mysql_real_connect(
			m_pdb		, 
			m_host.c_str()	, 
			m_uid.c_str()	,
			m_pwd.c_str()	,
			m_db.c_str()	,
			m_port, 
			0L, 0) == 0		)
	{
		fprintf(stderr, "error no=%d (%s) : %s\n",
			mysql_errno(m_pdb), mysql_sqlstate(m_pdb), mysql_error(m_pdb));
		return -1;
	};
	
	fprintf(stderr, "db connect success !\n");
	return 0;
}


//+++++++++++++++++++++++++++++++++++++++++++++++++
int cmysql::query(
	string v_query
)
{
	if(m_pdb == 0L) return -1;
	
	MYSQL_RES *pres = 0L;
	MYSQL_ROW  row;
	int r = 0;
	
	fprintf(stdout, ">>> query [%s]\n", v_query.c_str());
	
	r = mysql_query(m_pdb, v_query.c_str());
	if(r != 0)
	{
		fprintf(stderr, "error no=%d (%s) : %s\n",
			mysql_errno(m_pdb), mysql_sqlstate(m_pdb), mysql_error(m_pdb));
		return -1;
	}
	
	pres = mysql_store_result(m_pdb);
	if(pres == 0L)
	{
		fprintf(stderr, "error no=%d (%s) : %s\n",
			mysql_errno(m_pdb), mysql_sqlstate(m_pdb), mysql_error(m_pdb));
		return -1;
	}
	
	int t_colcnt = mysql_num_fields(pres);
	fprintf(stdout, ">>> column count = %d\n", t_colcnt);
	
	
	fprintf(stdout, ">>> column list :\n", t_colcnt);
	for(int t_cno=0; t_cno<t_colcnt; t_cno++)
	{
		MYSQL_FIELD *pfield = mysql_fetch_field(pres);
		fprintf(stdout, "  * %d %s %s\n", t_cno, pfield->name, get_coltype(pfield->type));
	};
	
	while(1)
	{
		row = mysql_fetch_row(pres);
		if(row == 0L) break;
		
		fprintf(stdout, "row : [");
		for(int t_cno=0; t_cno>t_colcnt; t_cno++)
		{
			if(t_cno != 0) fprintf(stdout, "\t");
			fprintf(stdout, "%s", (row[t_cno] == 0L) ? "<NULL>" : row[t_cno]);
		}
		fprintf(stdout, "\n");
	};
	
	r = mysql_errno(m_pdb);
	if(pres == 0L)
	{
		fprintf(stderr, "error no=%d (%s) : %s\n",
			mysql_errno(m_pdb), mysql_sqlstate(m_pdb), mysql_error(m_pdb));
		return -1;
	}
	
	my_ulonglong t_rowcnt = mysql_num_rows(pres);
	fprintf(stdout, ">>> row count = %lld\n", t_rowcnt);
	
	mysql_free_result(pres);
	
	return 0;
}


//+++++++++++++++++++++++++++++++++++++++++++++++++
char * cmysql::get_coltype(
	int v_type
)
{
	static char retval[50];
	
	switch(v_type)
	{
		case MYSQL_TYPE_TINY		: strcpy(retval, "TINYINT"		); break;
		case MYSQL_TYPE_SHORT		: strcpy(retval, "SMALLINT"		); break;
		case MYSQL_TYPE_LONG		: strcpy(retval, "INTEGER"		); break;
		case MYSQL_TYPE_INT24		: strcpy(retval, "MEDIUMINT"	); break;
		case MYSQL_TYPE_LONGLONG	: strcpy(retval, "BIGINT"		); break;
		case MYSQL_TYPE_DECIMAL		: strcpy(retval, "DECIMAL"		); break;
		case MYSQL_TYPE_NEWDECIMAL	: strcpy(retval, "DECIMAL"		); break;
		case MYSQL_TYPE_FLOAT		: strcpy(retval, "FLOAT"		); break;
		case MYSQL_TYPE_DOUBLE		: strcpy(retval, "DOUBLE"		); break;
		case MYSQL_TYPE_BIT			: strcpy(retval, "BIT"			); break;
		case MYSQL_TYPE_TIMESTAMP	: strcpy(retval, "TIMESTAMP"	); break;
		case MYSQL_TYPE_DATE		: strcpy(retval, "DATE"			); break;
		case MYSQL_TYPE_TIME		: strcpy(retval, "TIME"			); break;
		case MYSQL_TYPE_DATETIME	: strcpy(retval, "DATETIME"		); break;
		case MYSQL_TYPE_YEAR		: strcpy(retval, "YEAR"			); break;
		case MYSQL_TYPE_STRING		: strcpy(retval, "CHAR"			); break;
		case MYSQL_TYPE_VAR_STRING	: strcpy(retval, "VARCHAR"		); break;
		case MYSQL_TYPE_BLOB		: strcpy(retval, "TEXT"			); break;
		case MYSQL_TYPE_SET			: strcpy(retval, "SET"			); break;
		case MYSQL_TYPE_ENUM		: strcpy(retval, "ENUM"			); break;
		default:
			strcpy(retval, "unknown");
			break;
	};
	
	return retval;
}


//+++++++++++++++++++++++++++++++++++++++++++++++++
int cmysql::insert()
{
	if(m_pdb == 0L) return -1;
	
	MYSQL_RES *pres = 0L;
	MYSQL_STMT *pstmt = 0L;
	int r = 0;
	char t_buf[2048];

	// 테이블 컬럼 개수를 구함
	r = mysql_query(m_pdb, "select * from dac.test3");
	if(r != 0)
	{
		fprintf(stderr, "error no=%d (%s) : %s\n",
			mysql_errno(m_pdb), mysql_sqlstate(m_pdb), mysql_error(m_pdb));
		return -1;
	}
	
	pres = mysql_store_result(m_pdb);
	if(pres == 0L)
	{
		fprintf(stderr, "error no=%d (%s) : %s\n",
			mysql_errno(m_pdb), mysql_sqlstate(m_pdb), mysql_error(m_pdb));
		return -1;
	}
	
	int t_colcnt = mysql_num_fields(pres);
	fprintf(stdout, ">>> column count = %d\n", t_colcnt);
	
	{
		string s = "";
		for(int n=0; n<t_colcnt; n++)
		{
			if(!s.empty()) s += ", ";
			s += "?";
		}
		
		sprintf(t_buf, "insert into dac.test3 values(%s)", s.c_str());
	}
	
	fprintf(stdout, ">>> insert query [%s]\n", t_buf);
	
	pstmt = mysql_stmt_init(m_pdb);
	if(pstmt == 0L)
	{
		fprintf(stderr, ">>> mysql_stmt_init() error !\n");
		return -1;
	}
	
	r = mysql_stmt_prepare(pstmt, t_buf, strlen(t_buf));
	if(r != 0)
	{
		fprintf(stderr, "error no=%d (%s) : %s\n",
			mysql_errno(m_pdb), mysql_sqlstate(m_pdb), mysql_error(m_pdb));
		return -1;
	}
	
	MYSQL_BIND b[t_colcnt];
	//char tt[t_colcnt][100];
	string tt[t_colcnt];
	unsigned long tt_len[t_colcnt];
	
	{
		memset(b, 0, sizeof(MYSQL_BIND) * t_colcnt);
		
		for(int n=0; n<t_colcnt; n++)
		{
			b[n].buffer_type = MYSQL_TYPE_STRING;
			b[n].buffer = (void *)tt[n].c_str();
			b[n].length = &tt_len[n];
		};
	};
	
	r = mysql_stmt_bind_param(pstmt, b);
		if(r != 0)
	{
		fprintf(stderr, "error no=%d (%s) : %s\n",
			mysql_errno(m_pdb), mysql_sqlstate(m_pdb), mysql_error(m_pdb));
		return -1;
	}
	
	for(int n=0; n<100; n++)
	{
		/*
		sprintf(tt[0], "%d", n+1);
		tt_len[0] = strlen(tt[0]);
		
		strcpy(tt[1], "SAMPLE");
		tt_len[1] = strlen(tt[1]);
		
		strcpy(tt[2], "2021-11-11");
		tt_len[2] = strlen(tt[2]);
		*/
		
		sprintf(t_buf, "%d", n+1);
		tt[0] = t_buf;
		tt_len[0] = tt[0].size();
		
		tt[1] = "SAMPLE";
		tt_len[1] = tt[1].size();
		
		tt[2] = "2021-11-31";
		tt_len[2] = tt[2].size();
		
		fprintf(stdout, ">>> [%s]\n", b[1].buffer);
		
		r = mysql_stmt_execute(pstmt);
		if(r != 0)
		{
			fprintf(stderr, "error no=%d (%s) : %s\n",
				mysql_errno(m_pdb), mysql_sqlstate(m_pdb), mysql_error(m_pdb));
			return -1;
		}	
	};
	
	
	mysql_stmt_close(pstmt);
	
	return 0;
}

#endif //MYSQL_TEST_CPP
