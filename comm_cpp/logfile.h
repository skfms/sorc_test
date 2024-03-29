/**
 * @brief 로그 클래스 헤더
 * @author celizion
 * @version 1.0.0
 */

#ifndef LOGFILE_H
#define LOGFILE_H

#include <pthread.h>
#include <string>

using namespace std;

//+++++++++++++++++++++++++++++++++++++++++++++++++
/*! @class clogfile log.h
    @brief 로그 클래스
 */
class clogfile
{
public :
	 clogfile();
	~clogfile();
	
public:
	///@brief TRACE & NOLOG 는 로그 파일에 기록이 안됨
	enum E_LOGLEVEL
	{
		_TRACE=0,		///< 데이터 출력 및 프로세스 동작 확인 (파일 기록 안함)
		_DEBUG,			///< 중요 데이터 또는 프로세스 상태
		_INFO,			///< 중요 프로세스 상태 출력
		_WARN,			///< 경고 출력
		_ERROR,			///< 에러 풀력 (프로그램 기동)
		_CRITICAL,		///< 심각한 에러 출력(프로그램 중지)
		_NOLOG			///< 화면 출력
	};
	
public :
	int			rootopen(string v_logfile, string v_module);
	void		trace	(const char * v_format, ...	);
	void		debug	(const char * v_format, ...	);
	void		info	(const char * v_format, ...	);
	void		warn	(const char * v_format, ...	);
	void		error	(const char * v_format, ...	);
	void		critical(const char * v_format, ...	);
	void		nolog	(const char * v_format, ...	);
	void		write	(E_LOGLEVEL v_loglevel, const char * v_format, va_list v_arges	);

	E_LOGLEVEL	set_loglevel	(const char * v_debuglebel	);
	E_LOGLEVEL	get_loglevel	();
	string		get_loglevel	(E_LOGLEVEL v_loglevel);
	
	int			set_console		(int v_enable		);

private:
	FILE *		m_fp	;
	string 		m_logfile	;
	pthread_mutex_t	m_lock	;
	E_LOGLEVEL	m_level		;
	int			m_console	;
	string		m_path		;
	string		m_module	;
	
	void 		init ();
	void		close();

	string		get_date();
	int			open ();
};

#endif // LOGFILE_H

