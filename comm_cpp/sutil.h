/**
 * @brief 유틸리티 클래스 헤더
 * @author celizion
 * @version 1.0.0
 */

#ifndef SUTIL_H
#define SUTIL_H

#include "define.h"

using namespace std;

//+++++++++++++++++++++++++++++++++++++++++++++++++
/*! @class csutil sutil.h
    @brief 유틸리티 클래스
 */
class csutil
{
public :
	 csutil() {};
	~csutil() {};
	
public:
	///< 문자열 함수
	static string	str_replace	(const char * v_indata, string v_form, string v_to, int v_case = 0);
	static strvect	str_splite	(const char * v_indata, const char * v_delimiter);
	static string	str_ltrim	(const char * v_indata	);
	static string	str_rtrim	(const char * v_indata	);
	static string	str_trim	(const char * v_indata	);

	///< 입출력 함수
	static string io_readfile(const char * v_file);
	
	///< 시스템 함수
};

#endif // SUTIL_H

