/**
 * @brief 로그 클래스
 * @author celizion
 * @version 1.0.0
 */

#ifndef LOGFILE_CPP
#define LOGFILE_CPP

#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <stdarg.h>
#include <time.h>

#include <algorithm>

#include "logfile.h"

/*! Extern Variable */

/*! Global Variable */

/*! Local Variable	*/


//=================================================
///< clogfile class

//+++++++++++++++++++++++++++++++++++++++++++++++++
/*!
 * @brief clogfile 생성자
*/
clogfile::clogfile()
{
	init();
};


//+++++++++++++++++++++++++++++++++++++++++++++++++
/*!
 * @brief clogfile 소멸자
*/
clogfile::~clogfile()
{
	close();
};


//+++++++++++++++++++++++++++++++++++++++++++++++++
/*!
 * @brief clogfile 초기화
*/
void clogfile::init()
{
	m_fp = 0L;
	m_logfile = "";
	m_level = _INFO;
	m_console = 1;

	m_path = "";
	m_module = "";

	pthread_mutex_init(&m_lock, 0L);
};


//+++++++++++++++++++++++++++++++++++++++++++++++++
/*!
 * @brief clogfile 종료
*/
void clogfile::close()
{
	if(m_fp)
	{
		fclose(m_fp);
		m_fp = 0L;
	};
	pthread_mutex_destroy(&m_lock);
};


//+++++++++++++++++++++++++++++++++++++++++++++++++
/*!
 * @brief 로그파일 Open
 * @param [in] v_path 파일경로
 * @param [in] v_file 파일명
 * @return 0:true
*/
int clogfile::rootopen(
	string v_rootpath,
	string v_module
)
{
	int t_ret = 0;

	m_path = v_rootpath + "/log";
	m_module = v_module;
	
	return open();
}


//+++++++++++++++++++++++++++++++++++++++++++++++++
/*!
 * @brief 로그파일 Open
 * @return 0:true
*/
int clogfile::open()
{
	char t_file[200];
	sprintf(t_file, "%s/%s.log", m_path.c_str(), m_module.c_str());

	if(m_fp)
	{
		fclose(m_fp);
		m_fp = 0L;
	};

	if((m_fp = fopen(t_file, "a+")) == 0L)
	{
		fprintf(stderr,"*** log file open error : [%s]\n", t_file);
		return -1;
	}

	return 0;
}


//+++++++++++++++++++++++++++++++++++++++++++++++++
/*!
 * @brief TRACE 로그 출력
*/
void clogfile::trace
(
	const char * v_format,
	...
)
{
	va_list ap;
	
	va_start(ap, v_format);
	write(_TRACE, v_format, ap);
	va_end(ap);
};


//+++++++++++++++++++++++++++++++++++++++++++++++++
/*!
 * @brief DEBUG 로그 출력
*/
void clogfile::debug
(
	const char * v_format,
	...
)
{
	va_list ap;
	
	va_start(ap, v_format);
	write(_DEBUG, v_format, ap);
	va_end(ap);
};


//+++++++++++++++++++++++++++++++++++++++++++++++++
/*!
 * @brief INFO 로그 출력
*/
void clogfile::info
(
	const char * v_format,
	...
)
{
	va_list ap;
	
	va_start(ap, v_format);
	write(_INFO, v_format, ap);
	va_end(ap);
};


//+++++++++++++++++++++++++++++++++++++++++++++++++
/*!
 * @brief WARNNING 로그 출력
*/
void clogfile::warn
(
	const char * v_format,
	...
)
{
	va_list ap;
	
	va_start(ap, v_format);
	write(_WARN, v_format, ap);
	va_end(ap);
};


//+++++++++++++++++++++++++++++++++++++++++++++++++
/*!
 * @brief ERROR 로그 출력
*/
void clogfile::error
(
	const char * v_format,
	...
)
{
	va_list ap;
	
	va_start(ap, v_format);
	write(_ERROR, v_format, ap);
	va_end(ap);
};


//+++++++++++++++++++++++++++++++++++++++++++++++++
/*!
 * @brief CRITICAL 로그 출력
*/
void clogfile::critical
(
	const char * v_format,
	...
)
{
	va_list ap;
	
	va_start(ap, v_format);
	write(_CRITICAL, v_format, ap);
	va_end(ap);
};


//+++++++++++++++++++++++++++++++++++++++++++++++++
/*!
 * @brief NOLOG 로그 출력
*/
void clogfile::nolog
(
	const char * v_format,
	...
)
{
	va_list ap;
	
	va_start(ap, v_format);
	write(_NOLOG, v_format, ap);
	va_end(ap);
};


//+++++++++++++++++++++++++++++++++++++++++++++++++
/*!
 * @brief 설정된 로그 레빌에 따른 출력
 * @param [in] v_loglevel 출력 로그 레벨
 * @param [in] v_format 출력 형태
 * @param [in] v_args 인자값
*/
void clogfile::write
(
	E_LOGLEVEL v_loglevel,
	const char * v_format,
	va_list v_args
)
{
	///< _TRACE & _NOLOG 로그파일에 저장하지 않음
	if(v_loglevel != _TRACE && v_loglevel != _NOLOG)
	{
		if(m_level <= v_loglevel)
		{
			pthread_mutex_lock(&m_lock);

			if(m_fp)
			{
				string date = get_date();
				string level = get_loglevel(v_loglevel);

				va_list ap;
				va_copy(ap, v_args);

				fprintf (m_fp, "%s [%s] : ", date.c_str(), level.c_str());
				vfprintf(m_fp, v_format, ap);
				fprintf (m_fp, "\n");
				fflush  (m_fp);
			}

			pthread_mutex_unlock(&m_lock);
		}
	}
	
	if(m_console)
	{
		string level = get_loglevel(v_loglevel);

		va_list ap;
		va_copy(ap, v_args);

		fprintf (stderr, "[%-10s] [%s] : ", m_module.c_str(), level.c_str());
		vfprintf(stderr, v_format, ap);
		fprintf (stderr, "\n");
		fflush  (stderr);
	}
};


//+++++++++++++++++++++++++++++++++++++++++++++++++
/*!
 * @brief 현재 시간을 구함
 * @return 현재 일자 : 'YYYY-MM-DD HH:MI:SS' 형태
*/
string clogfile::get_date()
{
	string t_retstr = "";
	
	char stime[50];
	
	struct timespec st;
	
	clock_gettime(CLOCK_REALTIME, &st);
	struct tm *now = localtime(&st.tv_sec);
	long ms = st.tv_nsec;

	sprintf(stime,
		"%04d-%02d-%02d %02d:%02d:%02d.%06ld", 
		now->tm_year+1900, now->tm_mon+1, now->tm_mday, 
		now->tm_hour, now->tm_min, now->tm_sec, ms/1000);

	t_retstr = stime;
	return t_retstr;
}


//+++++++++++++++++++++++++++++++++++++++++++++++++
/*!
 * @brief 로그레벨을 설정
 * @return 설정된 로그레벨
*/
clogfile::E_LOGLEVEL clogfile::set_loglevel
(
	const char * v_loglevel
)
{
	string s = v_loglevel;
	transform(s.begin(), s.end(), s.begin(), ::toupper);

	// default
	m_level = _INFO;
	
	if		(s == "TRACE"	) m_level = _TRACE		;
	else if	(s == "DEBUG"	) m_level = _DEBUG		;
	else if	(s == "WARN"	) m_level = _WARN		;
	else if	(s == "ERROR"	) m_level = _ERROR		;
	else if	(s == "CRITICAL") m_level = _CRITICAL	;
	else if	(s == "NOLOG"	) m_level = _NOLOG		;

	return m_level;
}


//+++++++++++++++++++++++++++++++++++++++++++++++++
/*!
 * @return 설정된 로그레벨
*/
clogfile::E_LOGLEVEL clogfile::get_loglevel()
{
	return m_level;
}


//+++++++++++++++++++++++++++++++++++++++++++++++++
/*!
* @param [in] v_loglevel 로그 레벨
 * @return 입력된 로그레벨을 문자열로 촐력
*/
string clogfile::get_loglevel
(
	E_LOGLEVEL v_loglevel
)
{
	string t_retstr = "";
	
	switch(v_loglevel)
	{
		case _TRACE		: t_retstr = "TRACE   "; break;
		case _DEBUG		: t_retstr = "DEBUG   "; break;
		case _INFO		: t_retstr = "INFO    "; break;
		case _WARN		: t_retstr = "WARNING "; break;
		case _ERROR		: t_retstr = "ERROR   "; break;
		case _CRITICAL	: t_retstr = "CRITICAL"; break;
		case _NOLOG		: t_retstr = "NOLOG   "; break;
	};

	return t_retstr;
}


//+++++++++++++++++++++++++++++++++++++++++++++++++
/*!
* @param [in] v_enable 콘솔 출력 여부
 * @return 설정된 콘솔 출력 여부 값
*/
int clogfile::set_console
(
	int v_enable
)
{
	// default
	m_console = 1;
	
	if(v_enable == 0) m_console = 0;
	
	return m_console;
}

#endif // LOGFILE_CPP
