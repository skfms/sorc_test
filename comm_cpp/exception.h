/**
 * @brief json 클래스 헤더
 * @author celizion
 * @version 1.0.0
 */

#ifndef EXCEPTION_H
#define EXCEPTION_H

#include <string>

using namespace std;

//+++++++++++++++++++++++++++++++++++++++++++++++++
/*! @class cexception exception.h
    @brief exception 클래스
 */
class cexception
{
public :
	 cexception();
	 cexception(const char * v_formast, ...);
	 cexception(int v_code, const char * v_formast, ...);
	~cexception();
	
public:
	enum E_EXPCD {
		_UNSET=-1
	};

public :
	int code		();
	const char * message	();

private:
	int		m_code;
	string	m_message;

	void 	init 	();		///< 초기화
	void	close	();		///< 종료
	
	void	reset_code();	///< 코드 초기화
};

#endif // EXCEPTION_H

